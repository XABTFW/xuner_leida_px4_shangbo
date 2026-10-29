#include "cooperative_rendezvous.hpp"

#include <commander/px4_custom_mode.h>
#include <drivers/drv_hrt.h>
#include <lib/mathlib/mathlib.h>
#include <px4_platform_common/getopt.h>
#include <px4_platform_common/log.h>

#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

static constexpr float MAX_HORIZONTAL_SPEED_M_S = 50.f;
static constexpr float MAX_VERTICAL_SPEED_M_S = 5.f;
static constexpr float DEFAULT_HORIZONTAL_SLEW_M_S2 = 5.f;

CooperativeRendezvous::CooperativeRendezvous(const Options &options) :
	ModuleParams(nullptr),
	ScheduledWorkItem(MODULE_NAME, px4::wq_configurations::nav_and_controllers),
	_options(options),
	_shortcut_activation(options.shortcut_activation)
{
}

bool CooperativeRendezvous::init()
{
	ScheduleOnInterval(50_ms);
	return true;
}

void CooperativeRendezvous::update_params_if_needed()
{
	if (_parameter_update_sub.updated()) {
		parameter_update_s update{};
		_parameter_update_sub.copy(&update);
		updateParams();
	}
}

void CooperativeRendezvous::update_vehicle_id()
{
	if (_vehicle_id_initialized) {
		return;
	}

	int32_t mav_sys_id = 0;
	param_t handle = param_find("MAV_SYS_ID");

	if (handle != PARAM_INVALID && param_get(handle, &mav_sys_id) == PX4_OK && mav_sys_id > 0) {
		_vehicle_id = static_cast<uint32_t>(mav_sys_id);
		_vehicle_id_initialized = true;
	}
}

CooperativeRendezvous::Role CooperativeRendezvous::active_role() const
{
	if (_options.role != Role::Auto) {
		return _options.role;
	}

	return _vehicle_id == 2 ? Role::Rendezvous : Role::Broadcast;
}

float CooperativeRendezvous::aux_value(int index) const
{
	switch (index) {
	case 1: return _manual_control.aux1;
	case 2: return _manual_control.aux2;
	case 3: return _manual_control.aux3;
	case 4: return _manual_control.aux4;
	case 5: return _manual_control.aux5;
	case 6: return _manual_control.aux6;
	default: return NAN;
	}
}

bool CooperativeRendezvous::aux_switch_active(int index) const
{
	const float value = aux_value(index);
	return PX4_ISFINITE(value) && value > 0.5f;
}

bool CooperativeRendezvous::button_active(int button) const
{
	if (button < 0 || button > 15) {
		return false;
	}

	return (_manual_control.buttons & (1u << button)) != 0;
}

bool CooperativeRendezvous::rendezvous_switch_enabled() const
{
	const int act_aux = _param_act_aux.get();
	const int act_btn = _param_act_btn.get();

	return _shortcut_activation.load() || (act_aux == 0 && act_btn < 0) || aux_switch_active(act_aux)
	       || button_active(act_btn);
}

bool CooperativeRendezvous::dyt_guidance_active() const
{
	// Yield to the seeker only while it is actually commanding aircraft motion
	// (camera locked and tracking). While the seeker is just searching or has lost
	// the target it controls the gimbal only, so the position-sharing follower keeps
	// driving the aircraft. This is the single handoff boundary between the two
	// controllers so they never publish trajectory setpoints at the same time.
	return _dyt_guidance_status.controlling_vehicle && _dyt_guidance_status.timestamp != 0 &&
	       hrt_elapsed_time(&_dyt_guidance_status.timestamp) < 500_ms;
}

bool CooperativeRendezvous::local_position_valid(const vehicle_local_position_s &local_pos) const
{
	return local_pos.xy_valid && local_pos.z_valid &&
	       local_pos.xy_global && local_pos.z_global &&
	       PX4_ISFINITE(local_pos.x) && PX4_ISFINITE(local_pos.y) && PX4_ISFINITE(local_pos.z) &&
	       PX4_ISFINITE(local_pos.ref_lat) && PX4_ISFINITE(local_pos.ref_lon) && PX4_ISFINITE(local_pos.ref_alt);
}

bool CooperativeRendezvous::update_map_projection(const vehicle_local_position_s &local_pos)
{
	if (!local_position_valid(local_pos)) {
		return false;
	}

	if (!_map_ref_initialized) {
		_map_ref.initReference(local_pos.ref_lat, local_pos.ref_lon, local_pos.ref_timestamp);
		_map_ref_initialized = true;
		PX4_INFO("cooperative map ref: lat=%.7f lon=%.7f", local_pos.ref_lat, local_pos.ref_lon);
	}

	return true;
}

void CooperativeRendezvous::publish_own_position(const vehicle_local_position_s &local_pos)
{
	if (!_vehicle_id_initialized || !update_map_projection(local_pos)) {
		return;
	}

	double lat = static_cast<double>(NAN);
	double lon = static_cast<double>(NAN);
	_map_ref.reproject(local_pos.x, local_pos.y, lat, lon);

	cooperative_position_s position{};
	position.timestamp = hrt_absolute_time();
	position.mavid = _vehicle_id;
	position.lat = lat;
	position.lon = lon;
	position.alt = static_cast<double>(static_cast<float>(local_pos.ref_alt) - local_pos.z);
	position.vx = local_pos.vx;
	position.vy = local_pos.vy;
	position.vz = local_pos.vz;
	position.yaw = local_pos.heading_good_for_control ? local_pos.heading : static_cast<float>(NAN);
	position.yawspeed = local_pos.delta_heading;

	_cooperative_position_pub.publish(position);
}

bool CooperativeRendezvous::update_target_from_link()
{
	follower_info_s info{};
	bool updated = false;

	while (_follower_info_sub.update(&info)) {
		if (info.mavid == _options.target_id && info.mavid != _vehicle_id &&
		    PX4_ISFINITE(info.lat) && PX4_ISFINITE(info.lon) && PX4_ISFINITE(info.alt) && info.alt >= 0.0) {
			_target_info = info;
			// Preserve the MAVLink receive time. A module started later must not make an old cached uORB sample fresh again.
			_last_target_time = info.timestamp;
			updated = true;
		}
	}

	return updated;
}

bool CooperativeRendezvous::target_state_local(const vehicle_local_position_s &local_pos,
		matrix::Vector3f &target_position, matrix::Vector3f &target_velocity)
{
	if (!_map_ref_initialized || _last_target_time == 0) {
		reset_target_filter();
		return false;
	}

	if ((hrt_absolute_time() - _last_target_time) > static_cast<hrt_abstime>(_options.target_timeout_s * 1_s)) {
		reset_target_filter();
		return false;
	}

	float x = NAN;
	float y = NAN;
	_map_ref.project(_target_info.lat, _target_info.lon, x, y);

	if (!PX4_ISFINITE(x) || !PX4_ISFINITE(y)) {
		reset_target_filter();
		return false;
	}

	// Radar altitude is AGL. The local NED origin is the ground reference, so altitude above ground is negative NED z.
	matrix::Vector3f raw_position(x, y, -static_cast<float>(_target_info.alt));
	matrix::Vector3f raw_velocity(static_cast<float>(_target_info.vx), static_cast<float>(_target_info.vy),
				      static_cast<float>(_target_info.vz));

	if (!PX4_ISFINITE(raw_velocity(0)) || !PX4_ISFINITE(raw_velocity(1)) || !PX4_ISFINITE(raw_velocity(2))) {
		raw_velocity.zero();
	}

	apply_target_filter(raw_position, raw_velocity, target_position, target_velocity);

	if (_options.direct_target) {
		return PX4_ISFINITE(target_position(2));
	}

	float offset_x = _options.target_offset(0);
	float offset_y = _options.target_offset(1);

	if (_param_xy_offset_enable.get() > 0) {
		const float x_offset = _param_x_offset.get();
		const float y_offset = _param_y_offset.get();

		offset_x = PX4_ISFINITE(x_offset) ? x_offset : 0.f;
		offset_y = PX4_ISFINITE(y_offset) ? y_offset : 0.f;

	} else {
		const float target_distance = _param_dist.get();

		if (PX4_ISFINITE(target_distance) && target_distance >= 0.f) {
			const float offset_norm = sqrtf(offset_x * offset_x + offset_y * offset_y);

			if (offset_norm > 0.001f) {
				const float scale = target_distance / offset_norm;
				offset_x *= scale;
				offset_y *= scale;

			} else {
				offset_x = -target_distance;
				offset_y = 0.f;
			}
		}
	}

	target_position(0) += offset_x;
	target_position(1) += offset_y;
	target_position(2) += _options.target_offset(2) - _param_alt_diff.get();

	return PX4_ISFINITE(target_position(2));
}

void CooperativeRendezvous::apply_target_filter(const matrix::Vector3f &raw_position,
		const matrix::Vector3f &raw_velocity, matrix::Vector3f &target_position, matrix::Vector3f &target_velocity)
{
	const float position_tc = _param_target_position_tc.get();
	const float velocity_tc = _param_target_velocity_tc.get();
	const float max_position_jump = _param_target_position_jump.get();
	const bool filter_enabled = (PX4_ISFINITE(position_tc) && position_tc > 0.f) ||
				    (PX4_ISFINITE(velocity_tc) && velocity_tc > 0.f) ||
				    (PX4_ISFINITE(max_position_jump) && max_position_jump > 0.f);

	if (!filter_enabled) {
		reset_target_filter();
		target_position = raw_position;
		target_velocity = raw_velocity;
		return;
	}

	const hrt_abstime now = hrt_absolute_time();
	const bool new_sample = _last_target_filter_sample_time != _last_target_time;

	if (!_target_filter_initialized) {
		_target_position_input = raw_position;
		_target_position_filtered = raw_position;
		_target_velocity_input = raw_velocity;
		_target_velocity_filtered = raw_velocity;
		_last_target_filter_time = now;
		_last_target_filter_sample_time = _last_target_time;
		_target_filter_initialized = true;
	}

	if (new_sample) {
		matrix::Vector3f position_input = raw_position;

		if (PX4_ISFINITE(max_position_jump) && max_position_jump > 0.f) {
			const matrix::Vector3f delta = raw_position - _target_position_input;
			const float delta_norm = delta.norm();
			const float constrained_jump = math::constrain(max_position_jump, 0.1f, 200.f);

			if (PX4_ISFINITE(delta_norm) && delta_norm > constrained_jump) {
				position_input = _target_position_input + delta.normalized() * constrained_jump;
			}
		}

		_target_position_input = position_input;
		_target_velocity_input = raw_velocity;
		_last_target_filter_sample_time = _last_target_time;
	}

	const float dt = math::constrain((now - _last_target_filter_time) * 1e-6f, 0.005f, 0.5f);

	if (PX4_ISFINITE(position_tc) && position_tc > 0.f) {
		const float alpha = dt / (math::constrain(position_tc, 0.02f, 10.f) + dt);
		_target_position_filtered += (_target_position_input - _target_position_filtered) * alpha;

	} else {
		_target_position_filtered = _target_position_input;
	}

	if (PX4_ISFINITE(velocity_tc) && velocity_tc > 0.f) {
		const float alpha = dt / (math::constrain(velocity_tc, 0.02f, 10.f) + dt);
		_target_velocity_filtered += (_target_velocity_input - _target_velocity_filtered) * alpha;

	} else {
		_target_velocity_filtered = _target_velocity_input;
	}

	_last_target_filter_time = now;
	target_position = _target_position_filtered;
	target_velocity = _target_velocity_filtered;
}

void CooperativeRendezvous::reset_target_filter()
{
	_last_target_filter_time = 0;
	_last_target_filter_sample_time = 0;
	_target_filter_initialized = false;
	_target_position_input.zero();
	_target_position_filtered.zero();
	_target_velocity_input.zero();
	_target_velocity_filtered.zero();
}

bool CooperativeRendezvous::update_arrival_hold(matrix::Vector3f &target_position,
		matrix::Vector3f &target_velocity, const vehicle_local_position_s &local_pos, float &yaw)
{
	if (_param_arrival_hold_enable.get() <= 0) {
		reset_arrival_hold();
		return false;
	}

	const float hold_horizontal_radius = math::constrain(_param_arrival_hold_horizontal_radius.get(), 0.1f, 20.f);
	const float hold_vertical_radius = math::constrain(_param_arrival_hold_vertical_radius.get(), 0.1f, 20.f);
	const float hold_velocity = math::constrain(_param_arrival_hold_velocity.get(), 0.f, 10.f);
	const float hold_time_s = math::constrain(_param_arrival_hold_time.get(), 0.f, 10.f);
	const int32_t hold_mode = math::constrain(_param_arrival_hold_mode.get(), static_cast<int32_t>(0),
				  static_cast<int32_t>(2));
	const float release_radius = math::max(math::constrain(_param_arrival_hold_release.get(), 0.1f, 50.f),
					       math::max(hold_horizontal_radius, hold_vertical_radius));
	const hrt_abstime now = hrt_absolute_time();
	const matrix::Vector3f live_target_position = target_position;
	const matrix::Vector3f live_target_velocity = target_velocity;
	const matrix::Vector3f current_position(local_pos.x, local_pos.y, local_pos.z);
	const matrix::Vector3f position_error = live_target_position - current_position;
	const float horizontal_error = matrix::Vector2f(position_error(0), position_error(1)).norm();
	const float vertical_error = fabsf(position_error(2));
	const float target_horizontal_speed = matrix::Vector2f(live_target_velocity(0), live_target_velocity(1)).norm();
	const float target_vertical_speed = fabsf(live_target_velocity(2));
	const bool follower_velocity_valid = local_pos.v_xy_valid && local_pos.v_z_valid &&
					     PX4_ISFINITE(local_pos.vx) && PX4_ISFINITE(local_pos.vy) && PX4_ISFINITE(local_pos.vz);
	const matrix::Vector3f follower_velocity(local_pos.vx, local_pos.vy, local_pos.vz);
	const matrix::Vector3f relative_velocity = live_target_velocity - follower_velocity;
	const float relative_horizontal_speed = matrix::Vector2f(relative_velocity(0), relative_velocity(1)).norm();
	const float relative_vertical_speed = fabsf(relative_velocity(2));
	const float arrival_relative_speed = hold_mode == 1 ? relative_horizontal_speed :
					   (hold_mode == 2 ? relative_vertical_speed :
					    math::max(relative_horizontal_speed, relative_vertical_speed));
	const bool horizontal_arrived = horizontal_error <= hold_horizontal_radius;
	const bool vertical_arrived = vertical_error <= hold_vertical_radius;
	const bool position_arrived = hold_mode == 1 ? horizontal_arrived :
				      (hold_mode == 2 ? vertical_arrived : (horizontal_arrived && vertical_arrived));
	const bool relative_speed_arrived = follower_velocity_valid && arrival_relative_speed <= hold_velocity;
	const bool target_slow = target_horizontal_speed <= hold_velocity && target_vertical_speed <= hold_velocity;

	if (_arrival_hold_active) {
		const matrix::Vector3f live_delta = live_target_position - _arrival_hold_position;
		const float live_horizontal_delta = matrix::Vector2f(live_delta(0), live_delta(1)).norm();
		const float live_vertical_delta = fabsf(live_delta(2));

		if (live_horizontal_delta > release_radius || live_vertical_delta > release_radius) {
			PX4_INFO("cooperative rendezvous: arrival hold released delta=%.1fm",
				 (double)math::max(live_horizontal_delta, live_vertical_delta));
			reset_arrival_hold();

		} else {
			target_position = _arrival_hold_position;
			target_velocity.zero();

			if (PX4_ISFINITE(_arrival_hold_yaw)) {
				yaw = _arrival_hold_yaw;
			}

			return true;
		}
	}

	if (_arrival_follow_active) {
		if (horizontal_error > release_radius || vertical_error > release_radius) {
			PX4_INFO("cooperative rendezvous: arrival follow released error=%.1fm rel=%.1fm/s",
				 (double)math::max(horizontal_error, vertical_error), (double)arrival_relative_speed);
			reset_arrival_hold();

		} else if (target_slow && position_arrived && relative_speed_arrived) {
			if (_arrival_hold_candidate_since == 0) {
				_arrival_hold_candidate_since = now;

			} else if ((now - _arrival_hold_candidate_since) >= static_cast<hrt_abstime>(hold_time_s * 1_s)) {
				_arrival_follow_active = false;
				_arrival_hold_active = true;
				_arrival_hold_position = live_target_position;
				_arrival_hold_yaw = yaw;
				target_position = _arrival_hold_position;
				target_velocity.zero();
				PX4_INFO("cooperative rendezvous: arrival hold active setpoint=(%.1f %.1f %.1f)",
					 (double)_arrival_hold_position(0), (double)_arrival_hold_position(1),
					 (double)_arrival_hold_position(2));
			}

			return true;

		} else {
			_arrival_hold_candidate_since = 0;
			return true;
		}
	}

	// Capture a moving target as soon as it enters the arrival radius. From this
	// point the horizontal controller follows target velocity instead of chasing
	// an absolute point that may move behind the aircraft and command a U-turn.
	if (!target_slow && position_arrived) {
		_arrival_follow_active = true;
		_arrival_hold_candidate_since = 0;
		PX4_INFO("cooperative rendezvous: arrival follow active");
		return true;
	}

	// Do not suppress the approach command merely because a fast aircraft crosses
	// the hold radius. Arrival requires both position and relative velocity, as in
	// formation following where distance and speed are checked together.
	if (!position_arrived || !relative_speed_arrived) {
		_arrival_hold_candidate_since = 0;
		return false;
	}

	if (_arrival_hold_candidate_since == 0) {
		_arrival_hold_candidate_since = now;
		return true;
	}

	if ((now - _arrival_hold_candidate_since) < static_cast<hrt_abstime>(hold_time_s * 1_s)) {
		return true;
	}

	_arrival_hold_active = true;
	_arrival_hold_position = live_target_position;
	_arrival_hold_yaw = yaw;
	target_position = _arrival_hold_position;
	target_velocity.zero();
	PX4_INFO("cooperative rendezvous: arrival hold active setpoint=(%.1f %.1f %.1f)",
		 (double)_arrival_hold_position(0), (double)_arrival_hold_position(1),
		 (double)_arrival_hold_position(2));

	return true;
}

void CooperativeRendezvous::reset_arrival_hold()
{
	_arrival_hold_active = false;
	_arrival_follow_active = false;
	_arrival_hold_candidate_since = 0;
	_arrival_hold_position.zero();
	_arrival_hold_yaw = static_cast<float>(NAN);
}

void CooperativeRendezvous::publish_offboard_heartbeat(bool position_control, bool velocity_control)
{
	offboard_control_mode_s mode{};
	mode.timestamp = hrt_absolute_time();
	mode.position = position_control;
	mode.velocity = velocity_control;
	mode.acceleration = false;
	mode.attitude = false;
	mode.body_rate = false;
	_offboard_control_mode_pub.publish(mode);
}

void CooperativeRendezvous::publish_trajectory_setpoint(const matrix::Vector3f &position, const matrix::Vector3f &velocity,
		float yaw)
{
	trajectory_setpoint_s setpoint{};
	setpoint.timestamp = hrt_absolute_time();

	for (int i = 0; i < 3; i++) {
		setpoint.position[i] = position(i);
		setpoint.velocity[i] = velocity(i);
		setpoint.acceleration[i] = static_cast<float>(NAN);
		setpoint.jerk[i] = static_cast<float>(NAN);
	}

	setpoint.yaw = yaw;
	setpoint.yawspeed = static_cast<float>(NAN);
	_trajectory_setpoint_pub.publish(setpoint);
}

void CooperativeRendezvous::request_offboard(const vehicle_status_s &status)
{
	if (!_options.auto_offboard || status.nav_state == vehicle_status_s::NAVIGATION_STATE_OFFBOARD) {
		return;
	}

	const hrt_abstime now = hrt_absolute_time();

	if (now - _last_mode_request < 1_s) {
		return;
	}

	vehicle_command_s command{};
	command.timestamp = now;
	command.command = vehicle_command_s::VEHICLE_CMD_DO_SET_MODE;
	command.param1 = 1.f;
	command.param2 = PX4_CUSTOM_MAIN_MODE_OFFBOARD;
	command.target_system = status.system_id;
	command.target_component = status.component_id;
	command.source_system = status.system_id;
	command.source_component = status.component_id;
	command.from_external = false;
	_vehicle_command_pub.publish(command);
	_last_mode_request = now;
}

void CooperativeRendezvous::request_arm(const vehicle_status_s &status)
{
	if (!_options.auto_arm || status.arming_state == vehicle_status_s::ARMING_STATE_ARMED) {
		return;
	}

	const hrt_abstime now = hrt_absolute_time();

	if (now - _last_arm_request < 1_s) {
		return;
	}

	vehicle_command_s command{};
	command.timestamp = now;
	command.command = vehicle_command_s::VEHICLE_CMD_COMPONENT_ARM_DISARM;
	command.param1 = 1.f;
	command.target_system = status.system_id;
	command.target_component = status.component_id;
	command.source_system = status.system_id;
	command.source_component = status.component_id;
	command.from_external = false;
	_vehicle_command_pub.publish(command);
	_last_arm_request = now;
}

void CooperativeRendezvous::configure_relaxed_failsafes()
{
	if (!_options.relax_failsafes || _failsafes_configured) {
		return;
	}

	struct ParamSetInt {
		const char *name;
		int32_t value;
	};

	struct ParamSetFloat {
		const char *name;
		float value;
	};

	const ParamSetInt int_params[] = {
		{"NAV_DLL_ACT", 0},     // GCS datalink loss: disabled
		{"COM_DLL_EXCEPT", 7},  // ignore datalink loss in Mission/Hold/Offboard
		{"COM_RC_IN_MODE", 3},  // keep SITL RC/joystick input enabled instead of disabling sticks
		{"NAV_RCL_ACT", 1},     // RC loss fallback: Hold if it still triggers
		{"COM_RCL_EXCEPT", 7},  // ignore RC loss in Mission/Hold/Offboard
		{"COM_OBL_RC_ACT", 5},  // offboard loss fallback: Hold
	};

	const ParamSetFloat float_params[] = {
		{"COM_OF_LOSS_T", 5.f},
	};

	for (const ParamSetInt &item : int_params) {
		const param_t handle = param_find(item.name);

		if (handle != PARAM_INVALID) {
			param_set(handle, &item.value);
		}
	}

	for (const ParamSetFloat &item : float_params) {
		const param_t handle = param_find(item.name);

		if (handle != PARAM_INVALID) {
			param_set(handle, &item.value);
		}
	}

	_failsafes_configured = true;
	PX4_WARN("cooperative_rendezvous: relaxed simulation failsafes enabled");
}

void CooperativeRendezvous::hold_position(const vehicle_local_position_s &local_pos)
{
	keep_current_position_setpoint(local_pos);
}

void CooperativeRendezvous::keep_current_position_setpoint(const vehicle_local_position_s &local_pos)
{
	const matrix::Vector3f position(local_pos.x, local_pos.y, local_pos.z);
	const matrix::Vector3f velocity(0.f, 0.f, 0.f);

	publish_offboard_heartbeat(true, false);
	publish_trajectory_setpoint(position, velocity, local_pos.heading);
}

void CooperativeRendezvous::run_rendezvous(const vehicle_local_position_s &local_pos, const vehicle_status_s &status)
{
	matrix::Vector3f target_position{};
	matrix::Vector3f target_velocity{};

	if (!target_state_local(local_pos, target_position, target_velocity)) {
		const hrt_abstime now = hrt_absolute_time();

		if (now - _last_status_log > 2_s) {
			if (_last_target_time == 0) {
				PX4_WARN("cooperative rendezvous: waiting for target=%" PRIu32 " position", _options.target_id);

			} else {
				const double age_s = (double)(now - _last_target_time) * 1e-6;
				PX4_WARN("cooperative rendezvous: target=%" PRIu32 " position stale age=%.1fs",
					 _options.target_id, age_s);
			}

			_last_status_log = now;
		}

		hold_position(local_pos);

		// The shortcut workflow may take control only from the Hold state reached
		// after its guided takeoff. Land/RTL/manual selections remain pilot-owned.
		if (_shortcut_activation.load() && status.nav_state == vehicle_status_s::NAVIGATION_STATE_AUTO_LOITER) {
			request_offboard(status);
		}

		reset_velocity_slew();
		reset_arrival_hold();
		return;
	}

	matrix::Vector3f current_position(local_pos.x, local_pos.y, local_pos.z);
	matrix::Vector3f live_error = target_position - current_position;
	matrix::Vector2f live_horizontal_error(live_error(0), live_error(1));
	const float live_horizontal_distance = live_horizontal_error.norm();
	float yaw = PX4_ISFINITE(local_pos.heading) ? local_pos.heading : 0.f;

	if (live_horizontal_distance > 0.5f) {
		// NED yaw is measured clockwise from North: atan2(East error, North error).
		yaw = atan2f(live_horizontal_error(1), live_horizontal_error(0));
	}

	const bool arrival_holding = update_arrival_hold(target_position, target_velocity, local_pos, yaw);
	const bool arrival_following = _arrival_follow_active;
	matrix::Vector3f to_target = target_position - current_position;
	const float distance = to_target.norm();
	matrix::Vector3f velocity_sp = target_velocity;
	matrix::Vector2f horizontal_error(to_target(0), to_target(1));
	const float horizontal_distance = horizontal_error.norm();
	const float configured_speed = _param_app_speed.get();
	const float closing_speed = PX4_ISFINITE(configured_speed) && configured_speed > 0.f ?
				     math::constrain(configured_speed, 0.5f, MAX_HORIZONTAL_SPEED_M_S) :
				     math::constrain(_options.max_speed, 0.5f, MAX_HORIZONTAL_SPEED_M_S);
	const float slow_radius = math::max(_param_slow_radius.get(), 0.5f);
	const float configured_slew = _param_velocity_slew.get();
	const float braking_acceleration = PX4_ISFINITE(configured_slew) && configured_slew > 0.f ?
					   math::constrain(configured_slew, 0.1f, 20.f) : DEFAULT_HORIZONTAL_SLEW_M_S2;
	const float capture_radius = _param_arrival_hold_enable.get() > 0 ?
				     math::constrain(_param_arrival_hold_horizontal_radius.get(), 0.1f, 20.f) : 0.5f;

	if (!arrival_holding && horizontal_distance > 0.5f) {
		const float speed_scale = math::constrain(horizontal_distance / slow_radius, 0.f, 1.f);
		const float distance_to_capture = math::max(horizontal_distance - capture_radius, 0.f);
		const float braking_speed = sqrtf(2.f * braking_acceleration * distance_to_capture);
		const float approach_speed = math::min(closing_speed * speed_scale, braking_speed);
		const matrix::Vector2f approach_xy = horizontal_error / horizontal_distance * approach_speed;
		velocity_sp(0) += approach_xy(0);
		velocity_sp(1) += approach_xy(1);
	}

	// Position control handles vertical position error. Keep target velocity only as bounded feed-forward.
	velocity_sp(2) = math::constrain(velocity_sp(2), -MAX_VERTICAL_SPEED_M_S, MAX_VERTICAL_SPEED_M_S);

	matrix::Vector2f velocity_sp_xy(velocity_sp);
	float horizontal_speed = velocity_sp_xy.norm();

	if (PX4_ISFINITE(horizontal_speed) && horizontal_speed > MAX_HORIZONTAL_SPEED_M_S) {
		velocity_sp_xy *= MAX_HORIZONTAL_SPEED_M_S / horizontal_speed;
	}

	velocity_sp(0) = velocity_sp_xy(0);
	velocity_sp(1) = velocity_sp_xy(1);

	if (_arrival_hold_active) {
		reset_velocity_slew();

	} else {
		slew_horizontal_velocity(velocity_sp, local_pos);
	}

	velocity_sp_xy = matrix::Vector2f(velocity_sp);
	horizontal_speed = velocity_sp_xy.norm();

	if (PX4_ISFINITE(horizontal_speed) && horizontal_speed > MAX_HORIZONTAL_SPEED_M_S) {
		velocity_sp_xy *= MAX_HORIZONTAL_SPEED_M_S / horizontal_speed;
		velocity_sp(0) = velocity_sp_xy(0);
		velocity_sp(1) = velocity_sp_xy(1);
	}

	matrix::Vector3f control_position = target_position;

	if (!_arrival_hold_active) {
		// Horizontal tracking is generated explicitly above. Do not also feed the
		// horizontal position error into PX4's position loop, otherwise that hidden
		// correction can defeat the braking profile and command a U-turn after crossing.
		// Altitude remains position-controlled through control_position(2).
		control_position(0) = NAN;
		control_position(1) = NAN;
	}

	if (arrival_following) {
		const matrix::Vector2f target_velocity_xy(target_velocity);

		if (target_velocity_xy.norm() > 0.5f) {
			yaw = atan2f(target_velocity(1), target_velocity(0));
		}

	} else if (!_arrival_hold_active && horizontal_distance <= capture_radius && PX4_ISFINITE(local_pos.heading)) {
		// A slow/stationary target can move from just ahead to just behind while the
		// follower is braking. Keep current heading in the capture radius instead of
		// flipping yaw by 180 degrees for that small sign change in position error.
		yaw = local_pos.heading;
	}

	publish_offboard_heartbeat(true, false);
	publish_trajectory_setpoint(control_position, velocity_sp, yaw);

	request_arm(status);

	const bool shortcut_takeover = _shortcut_activation.load()
				       && status.nav_state == vehicle_status_s::NAVIGATION_STATE_AUTO_LOITER;
	const bool regular_takeover = !_shortcut_activation.load()
			      && (_options.direct_target ||
				  (status.nav_state != vehicle_status_s::NAVIGATION_STATE_AUTO_MISSION &&
				   status.nav_state != vehicle_status_s::NAVIGATION_STATE_AUTO_LOITER &&
				   status.nav_state != vehicle_status_s::NAVIGATION_STATE_AUTO_RTL &&
				   status.nav_state != vehicle_status_s::NAVIGATION_STATE_AUTO_LAND));

	if (shortcut_takeover || regular_takeover) {
		request_offboard(status);
	}

	const hrt_abstime now = hrt_absolute_time();

	if (now - _last_status_log > 2_s) {
		PX4_INFO("cooperative rendezvous: target=%" PRIu32
			 " distance=%.1fm app_spd=%.1fm/s hold=%d follow=%d target_ned=(%.1f %.1f %.1f)"
			 " vel_sp=(%.1f %.1f %.1f)",
			 _options.target_id, (double)distance,
			 (double)closing_speed, arrival_holding, arrival_following,
			 (double)target_position(0), (double)target_position(1), (double)target_position(2),
			 (double)velocity_sp(0), (double)velocity_sp(1), (double)velocity_sp(2));
		_last_status_log = now;
	}
}

void CooperativeRendezvous::slew_horizontal_velocity(matrix::Vector3f &velocity_sp,
		const vehicle_local_position_s &local_pos)
{
	const float configured_slew_rate = _param_velocity_slew.get();
	const float slew_rate = PX4_ISFINITE(configured_slew_rate) && configured_slew_rate > 0.f ?
				math::constrain(configured_slew_rate, 0.1f, 20.f) : DEFAULT_HORIZONTAL_SLEW_M_S2;

	const hrt_abstime now = hrt_absolute_time();
	matrix::Vector2f target_velocity_xy(velocity_sp(0), velocity_sp(1));

	if (!PX4_ISFINITE(target_velocity_xy(0)) || !PX4_ISFINITE(target_velocity_xy(1))) {
		target_velocity_xy.zero();
	}

	if (_last_velocity_slew_time == 0) {
		_last_velocity_sp_xy(0) = PX4_ISFINITE(local_pos.vx) ? local_pos.vx : 0.f;
		_last_velocity_sp_xy(1) = PX4_ISFINITE(local_pos.vy) ? local_pos.vy : 0.f;
		_last_velocity_slew_time = now;
	}

	if (!PX4_ISFINITE(_last_velocity_sp_xy(0)) || !PX4_ISFINITE(_last_velocity_sp_xy(1))) {
		_last_velocity_sp_xy.zero();
	}

	const float dt = math::constrain((now - _last_velocity_slew_time) * 1e-6f, 0.005f, 0.2f);
	const float max_delta = slew_rate * dt;
	const matrix::Vector2f delta = target_velocity_xy - _last_velocity_sp_xy;

	if (delta.norm() > max_delta) {
		target_velocity_xy = _last_velocity_sp_xy + delta.normalized() * max_delta;
	}

	_last_velocity_sp_xy = target_velocity_xy;
	_last_velocity_slew_time = now;
	velocity_sp(0) = target_velocity_xy(0);
	velocity_sp(1) = target_velocity_xy(1);
}

void CooperativeRendezvous::reset_velocity_slew()
{
	_last_velocity_slew_time = 0;
	_last_velocity_sp_xy.zero();
}

void CooperativeRendezvous::Run()
{
	if (should_exit()) {
		ScheduleClear();
		exit_and_cleanup();
		return;
	}

	uint8_t shortcut_request = _shortcut_request.load();

	if (shortcut_request != 0 && _shortcut_request.compare_exchange(&shortcut_request, 0)) {
		const bool activate = shortcut_request == 1;
		_shortcut_activation.store(activate);
		_offboard_user_released = !activate;
		reset_velocity_slew();
		reset_target_filter();
		reset_arrival_hold();
	}

	update_params_if_needed();
	update_vehicle_id();
	configure_relaxed_failsafes();

	vehicle_local_position_s local_pos{};
	vehicle_status_s status{};
	_vehicle_local_position_sub.copy(&local_pos);
	_vehicle_status_sub.copy(&status);
	_manual_control_sub.update(&_manual_control);
	_dyt_guidance_status_sub.update(&_dyt_guidance_status);

	const bool offboard_active = status.nav_state == vehicle_status_s::NAVIGATION_STATE_OFFBOARD;

	if (offboard_active && !_offboard_active_previous) {
		_offboard_was_active = true;
		_offboard_user_released = false;
		reset_velocity_slew();
		reset_arrival_hold();

	} else if (!offboard_active && _offboard_active_previous) {
		// A mode change after entering Offboard is treated as an explicit pilot release.
		// Stop publishing setpoints and requesting Offboard until the pilot selects it again.
		_offboard_user_released = true;
		reset_velocity_slew();
		reset_target_filter();
		reset_arrival_hold();
	}

	_offboard_active_previous = offboard_active;

	if (local_position_valid(local_pos)) {
		publish_own_position(local_pos);
	}

	update_target_from_link();

	if (!local_position_valid(local_pos)) {
		return;
	}

	if (active_role() == Role::Rendezvous) {
		if (!rendezvous_switch_enabled() || dyt_guidance_active()) {
			reset_velocity_slew();
			reset_target_filter();
			reset_arrival_hold();
			_offboard_was_active = false;
			_offboard_active_previous = offboard_active;
			_offboard_user_released = false;
			return;
		}

		if (_offboard_user_released && !offboard_active) {
			reset_velocity_slew();
			reset_target_filter();
			reset_arrival_hold();
			return;
		}

		run_rendezvous(local_pos, status);

	} else if (active_role() == Role::Broadcast && status.arming_state == vehicle_status_s::ARMING_STATE_ARMED &&
		   rendezvous_switch_enabled() && !dyt_guidance_active()) {
		reset_velocity_slew();
		reset_target_filter();
		reset_arrival_hold();
		keep_current_position_setpoint(local_pos);

	} else {
		reset_velocity_slew();
		reset_target_filter();
		reset_arrival_hold();
	}
}

int CooperativeRendezvous::print_status()
{
	const char *role = "auto";

	switch (active_role()) {
	case Role::Broadcast:
		role = "broadcast";
		break;

	case Role::Rendezvous:
		role = "rendezvous";
		break;

	case Role::Auto:
		break;
	}

	PX4_INFO("running: vehicle=%" PRIu32 " role=%s target=%" PRIu32 " direct=%d offset=(%.1f %.1f %.1f) xy_en=%ld xy=(%.1f %.1f) dist=%.1f app_spd=%.1f slow=%.1f vslew=%.1f tpos_tc=%.2f tvel_tc=%.2f tpos_jmp=%.1f alt_diff=%.1f",
		 _vehicle_id, role, _options.target_id,
		 static_cast<int>(_options.direct_target),
		 (double)_options.target_offset(0),
		 (double)_options.target_offset(1),
		 (double)_options.target_offset(2),
		 static_cast<long>(_param_xy_offset_enable.get()),
		 (double)_param_x_offset.get(),
		 (double)_param_y_offset.get(),
		 (double)_param_dist.get(),
		 (double)_param_app_speed.get(),
		 (double)_param_slow_radius.get(),
		 (double)_param_velocity_slew.get(),
		 (double)_param_target_position_tc.get(),
		 (double)_param_target_velocity_tc.get(),
		 (double)_param_target_position_jump.get(),
		 (double)_param_alt_diff.get());
	PX4_INFO("activation aux=%d enabled=%d dyt_active=%d user_released=%d",
		 static_cast<int>(_param_act_aux.get()), rendezvous_switch_enabled(), dyt_guidance_active(),
		 static_cast<int>(_offboard_user_released));
	PX4_INFO("activation button=%d buttons=0x%04x",
		 static_cast<int>(_param_act_btn.get()), static_cast<unsigned>(_manual_control.buttons));
	PX4_INFO("arrival hold: en=%ld hold=%d follow=%d mode=%ld hrad=%.1f vrad=%.1f vel=%.2f time=%.1f rel=%.1f",
		 static_cast<long>(_param_arrival_hold_enable.get()), _arrival_hold_active, _arrival_follow_active,
		 static_cast<long>(_param_arrival_hold_mode.get()),
		 (double)_param_arrival_hold_horizontal_radius.get(),
		 (double)_param_arrival_hold_vertical_radius.get(),
		 (double)_param_arrival_hold_velocity.get(), (double)_param_arrival_hold_time.get(),
		 (double)_param_arrival_hold_release.get());
	PX4_INFO("radar control: altitude=AGL xy=braking_velocity z=position xy_max=%.1fm/s z_ff_max=%.1fm/s",
		 (double)MAX_HORIZONTAL_SPEED_M_S, (double)MAX_VERTICAL_SPEED_M_S);
	return 0;
}

static bool parse_role(const char *arg, CooperativeRendezvous::Role &role)
{
	if (!strcmp(arg, "auto")) {
		role = CooperativeRendezvous::Role::Auto;
		return true;
	}

	if (!strcmp(arg, "broadcast")) {
		role = CooperativeRendezvous::Role::Broadcast;
		return true;
	}

	if (!strcmp(arg, "rendezvous")) {
		role = CooperativeRendezvous::Role::Rendezvous;
		return true;
	}

	return false;
}

int CooperativeRendezvous::task_spawn(int argc, char *argv[])
{
	Options options{};
	bool error_flag = false;
	bool offset_x_set = false;

	int myoptind = 1;
	int ch;
	const char *myoptarg = nullptr;

	while ((ch = px4_getopt(argc, argv, "r:t:d:x:y:z:v:T:AGFQh", &myoptind, &myoptarg)) != EOF) {
		switch (ch) {
		case 'r':
			if (!parse_role(myoptarg, options.role)) {
				error_flag = true;
			}
			break;

		case 't':
			options.target_id = strtoul(myoptarg, nullptr, 10);
			break;

		case 'd':
			if (!offset_x_set) {
				options.target_offset(0) = -fabsf(strtof(myoptarg, nullptr));
			}
			break;

		case 'x':
			options.target_offset(0) = strtof(myoptarg, nullptr);
			offset_x_set = true;
			break;

		case 'y':
			options.target_offset(1) = strtof(myoptarg, nullptr);
			break;

		case 'z':
			options.target_offset(2) = strtof(myoptarg, nullptr);
			break;

		case 'v':
			options.max_speed = math::constrain(strtof(myoptarg, nullptr), 0.5f, MAX_HORIZONTAL_SPEED_M_S);
			break;

		case 'T':
			options.target_timeout_s = math::constrain(strtof(myoptarg, nullptr), 0.5f, 30.f);
			break;

		case 'A':
			options.auto_arm = true;
			break;

		case 'F':
			options.relax_failsafes = true;
			break;

		case 'G':
			options.direct_target = true;
			options.target_offset.zero();
			break;

		case 'Q':
			options.shortcut_activation = true;
			break;

		case 'h':
		case '?':
		default:
			error_flag = true;
			break;
		}
	}

	if (error_flag) {
		return PX4_ERROR;
	}

	CooperativeRendezvous *instance = new CooperativeRendezvous(options);

	if (instance) {
		_object.store(instance);
		_task_id = task_id_is_work_queue;

		if (instance->init()) {
			return PX4_OK;
		}
	}

	delete instance;
	_object.store(nullptr);
	_task_id = -1;

	return PX4_ERROR;
}

int CooperativeRendezvous::custom_command(int argc, char *argv[])
{
	if (!is_running()) {
		return print_usage("module not running");
	}

	if (!strcmp(argv[0], "activate")) {
		CooperativeRendezvous *const instance = get_instance();
		instance->_shortcut_request.store(1);
		return PX4_OK;
	}

	if (!strcmp(argv[0], "deactivate")) {
		CooperativeRendezvous *const instance = get_instance();
		instance->_shortcut_request.store(2);
		return PX4_OK;
	}

	return print_usage("unknown command");
}

int CooperativeRendezvous::print_usage(const char *reason)
{
	if (reason) {
		PX4_WARN("%s\n", reason);
	}

	PRINT_MODULE_DESCRIPTION(
		R"DESCR_STR(
### Description
Two-aircraft cooperative rendezvous module.

MAV_SYS_ID=1 broadcasts its local position converted to WGS84.
MAV_SYS_ID=2 flies to a configurable offset near aircraft 1, or directly to
an incoming radar target position when -G is enabled.
)DESCR_STR");

	PRINT_MODULE_USAGE_NAME("cooperative_rendezvous", "controller");
	PRINT_MODULE_USAGE_COMMAND("start");
	PRINT_MODULE_USAGE_COMMAND("activate");
	PRINT_MODULE_USAGE_COMMAND("deactivate");
	PRINT_MODULE_USAGE_PARAM_STRING('r', "auto", "auto|broadcast|rendezvous", "Role selection", true);
	PRINT_MODULE_USAGE_PARAM_INT('t', 1, 1, 255, "Target MAV_SYS_ID for rendezvous", true);
	PRINT_MODULE_USAGE_PARAM_FLOAT('d', 5.f, 0.f, 100.f, "Distance behind target when x offset is not set", true);
	PRINT_MODULE_USAGE_PARAM_FLOAT('x', -5.f, -100.f, 100.f, "Target NED x offset", true);
	PRINT_MODULE_USAGE_PARAM_FLOAT('y', 0.f, -100.f, 100.f, "Target NED y offset", true);
	PRINT_MODULE_USAGE_PARAM_FLOAT('z', 0.f, -50.f, 50.f, "Target NED z offset", true);
	PRINT_MODULE_USAGE_PARAM_FLOAT('v', 3.f, 0.5f, MAX_HORIZONTAL_SPEED_M_S, "Maximum approach speed", true);
	PRINT_MODULE_USAGE_PARAM_FLOAT('T', 5.f, 0.5f, 30.f, "Target timeout", true);
	PRINT_MODULE_USAGE_PARAM_FLAG('A', "Auto arm rendezvous aircraft", true);
	PRINT_MODULE_USAGE_PARAM_FLAG('G', "Go directly to target position without offset/distance", true);
	PRINT_MODULE_USAGE_PARAM_FLAG('F', "Relax link/manual/offboard failsafes for simulation", true);
	PRINT_MODULE_USAGE_PARAM_FLAG('Q', "Temporarily activate rendezvous for a QGC shortcut workflow", true);
	PRINT_MODULE_USAGE_DEFAULT_COMMANDS();

	return 0;
}

extern "C" __EXPORT int cooperative_rendezvous_main(int argc, char *argv[])
{
	return CooperativeRendezvous::main(argc, argv);
}
