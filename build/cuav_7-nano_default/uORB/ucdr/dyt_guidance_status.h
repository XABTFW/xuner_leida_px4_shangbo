/****************************************************************************
 *
 *   Copyright (C) 2013-2022 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/


// auto-generated file

#pragma once

#include <ucdr/microcdr.h>
#include <string.h>
#include <uORB/topics/dyt_guidance_status.h>


static inline constexpr int ucdr_topic_size_dyt_guidance_status()
{
	return 88;
}

static inline bool ucdr_serialize_dyt_guidance_status(const void* data, ucdrBuffer& buf, int64_t time_offset = 0)
{
	const dyt_guidance_status_s& topic = *static_cast<const dyt_guidance_status_s*>(data);
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	const uint64_t timestamp_adjusted = topic.timestamp + time_offset;
	memcpy(buf.iterator, &timestamp_adjusted, sizeof(topic.timestamp));
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.state) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.state, sizeof(topic.state));
	buf.iterator += sizeof(topic.state);
	buf.offset += sizeof(topic.state);
	static_assert(sizeof(topic.requested_submode) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.requested_submode, sizeof(topic.requested_submode));
	buf.iterator += sizeof(topic.requested_submode);
	buf.offset += sizeof(topic.requested_submode);
	static_assert(sizeof(topic.active_submode) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.active_submode, sizeof(topic.active_submode));
	buf.iterator += sizeof(topic.active_submode);
	buf.offset += sizeof(topic.active_submode);
	static_assert(sizeof(topic.lost_reason) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.lost_reason, sizeof(topic.lost_reason));
	buf.iterator += sizeof(topic.lost_reason);
	buf.offset += sizeof(topic.lost_reason);
	static_assert(sizeof(topic.active) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.active, sizeof(topic.active));
	buf.iterator += sizeof(topic.active);
	buf.offset += sizeof(topic.active);
	static_assert(sizeof(topic.target_locked) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.target_locked, sizeof(topic.target_locked));
	buf.iterator += sizeof(topic.target_locked);
	buf.offset += sizeof(topic.target_locked);
	static_assert(sizeof(topic.controlling_vehicle) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.controlling_vehicle, sizeof(topic.controlling_vehicle));
	buf.iterator += sizeof(topic.controlling_vehicle);
	buf.offset += sizeof(topic.controlling_vehicle);
	static_assert(sizeof(topic.target_fresh) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.target_fresh, sizeof(topic.target_fresh));
	buf.iterator += sizeof(topic.target_fresh);
	buf.offset += sizeof(topic.target_fresh);
	static_assert(sizeof(topic.intercept_allowed) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.intercept_allowed, sizeof(topic.intercept_allowed));
	buf.iterator += sizeof(topic.intercept_allowed);
	buf.offset += sizeof(topic.intercept_allowed);
	buf.iterator += 3; // padding
	buf.offset += 3; // padding
	static_assert(sizeof(topic.los_age_s) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.los_age_s, sizeof(topic.los_age_s));
	buf.iterator += sizeof(topic.los_age_s);
	buf.offset += sizeof(topic.los_age_s);
	static_assert(sizeof(topic.frame_dt_s) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.frame_dt_s, sizeof(topic.frame_dt_s));
	buf.iterator += sizeof(topic.frame_dt_s);
	buf.offset += sizeof(topic.frame_dt_s);
	static_assert(sizeof(topic.delay_s) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.delay_s, sizeof(topic.delay_s));
	buf.iterator += sizeof(topic.delay_s);
	buf.offset += sizeof(topic.delay_s);
	static_assert(sizeof(topic.los_ned) == 12, "size mismatch");
	memcpy(buf.iterator, &topic.los_ned, sizeof(topic.los_ned));
	buf.iterator += sizeof(topic.los_ned);
	buf.offset += sizeof(topic.los_ned);
	static_assert(sizeof(topic.omega_los_ned) == 12, "size mismatch");
	memcpy(buf.iterator, &topic.omega_los_ned, sizeof(topic.omega_los_ned));
	buf.iterator += sizeof(topic.omega_los_ned);
	buf.offset += sizeof(topic.omega_los_ned);
	static_assert(sizeof(topic.velocity_sp) == 12, "size mismatch");
	memcpy(buf.iterator, &topic.velocity_sp, sizeof(topic.velocity_sp));
	buf.iterator += sizeof(topic.velocity_sp);
	buf.offset += sizeof(topic.velocity_sp);
	static_assert(sizeof(topic.acceleration_sp) == 12, "size mismatch");
	memcpy(buf.iterator, &topic.acceleration_sp, sizeof(topic.acceleration_sp));
	buf.iterator += sizeof(topic.acceleration_sp);
	buf.offset += sizeof(topic.acceleration_sp);
	static_assert(sizeof(topic.yaw_sp) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.yaw_sp, sizeof(topic.yaw_sp));
	buf.iterator += sizeof(topic.yaw_sp);
	buf.offset += sizeof(topic.yaw_sp);
	static_assert(sizeof(topic.yaw_rate_sp) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.yaw_rate_sp, sizeof(topic.yaw_rate_sp));
	buf.iterator += sizeof(topic.yaw_rate_sp);
	buf.offset += sizeof(topic.yaw_rate_sp);
	return true;
}

static inline bool ucdr_deserialize_dyt_guidance_status(ucdrBuffer& buf, dyt_guidance_status_s& topic, int64_t time_offset = 0)
{
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	memcpy(&topic.timestamp, buf.iterator, sizeof(topic.timestamp));
	if (topic.timestamp == 0) topic.timestamp = hrt_absolute_time();
	else topic.timestamp = math::min(topic.timestamp - time_offset, hrt_absolute_time());
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.state) == 1, "size mismatch");
	memcpy(&topic.state, buf.iterator, sizeof(topic.state));
	buf.iterator += sizeof(topic.state);
	buf.offset += sizeof(topic.state);
	static_assert(sizeof(topic.requested_submode) == 1, "size mismatch");
	memcpy(&topic.requested_submode, buf.iterator, sizeof(topic.requested_submode));
	buf.iterator += sizeof(topic.requested_submode);
	buf.offset += sizeof(topic.requested_submode);
	static_assert(sizeof(topic.active_submode) == 1, "size mismatch");
	memcpy(&topic.active_submode, buf.iterator, sizeof(topic.active_submode));
	buf.iterator += sizeof(topic.active_submode);
	buf.offset += sizeof(topic.active_submode);
	static_assert(sizeof(topic.lost_reason) == 1, "size mismatch");
	memcpy(&topic.lost_reason, buf.iterator, sizeof(topic.lost_reason));
	buf.iterator += sizeof(topic.lost_reason);
	buf.offset += sizeof(topic.lost_reason);
	static_assert(sizeof(topic.active) == 1, "size mismatch");
	memcpy(&topic.active, buf.iterator, sizeof(topic.active));
	buf.iterator += sizeof(topic.active);
	buf.offset += sizeof(topic.active);
	static_assert(sizeof(topic.target_locked) == 1, "size mismatch");
	memcpy(&topic.target_locked, buf.iterator, sizeof(topic.target_locked));
	buf.iterator += sizeof(topic.target_locked);
	buf.offset += sizeof(topic.target_locked);
	static_assert(sizeof(topic.controlling_vehicle) == 1, "size mismatch");
	memcpy(&topic.controlling_vehicle, buf.iterator, sizeof(topic.controlling_vehicle));
	buf.iterator += sizeof(topic.controlling_vehicle);
	buf.offset += sizeof(topic.controlling_vehicle);
	static_assert(sizeof(topic.target_fresh) == 1, "size mismatch");
	memcpy(&topic.target_fresh, buf.iterator, sizeof(topic.target_fresh));
	buf.iterator += sizeof(topic.target_fresh);
	buf.offset += sizeof(topic.target_fresh);
	static_assert(sizeof(topic.intercept_allowed) == 1, "size mismatch");
	memcpy(&topic.intercept_allowed, buf.iterator, sizeof(topic.intercept_allowed));
	buf.iterator += sizeof(topic.intercept_allowed);
	buf.offset += sizeof(topic.intercept_allowed);
	buf.iterator += 3; // padding
	buf.offset += 3; // padding
	static_assert(sizeof(topic.los_age_s) == 4, "size mismatch");
	memcpy(&topic.los_age_s, buf.iterator, sizeof(topic.los_age_s));
	buf.iterator += sizeof(topic.los_age_s);
	buf.offset += sizeof(topic.los_age_s);
	static_assert(sizeof(topic.frame_dt_s) == 4, "size mismatch");
	memcpy(&topic.frame_dt_s, buf.iterator, sizeof(topic.frame_dt_s));
	buf.iterator += sizeof(topic.frame_dt_s);
	buf.offset += sizeof(topic.frame_dt_s);
	static_assert(sizeof(topic.delay_s) == 4, "size mismatch");
	memcpy(&topic.delay_s, buf.iterator, sizeof(topic.delay_s));
	buf.iterator += sizeof(topic.delay_s);
	buf.offset += sizeof(topic.delay_s);
	static_assert(sizeof(topic.los_ned) == 12, "size mismatch");
	memcpy(&topic.los_ned, buf.iterator, sizeof(topic.los_ned));
	buf.iterator += sizeof(topic.los_ned);
	buf.offset += sizeof(topic.los_ned);
	static_assert(sizeof(topic.omega_los_ned) == 12, "size mismatch");
	memcpy(&topic.omega_los_ned, buf.iterator, sizeof(topic.omega_los_ned));
	buf.iterator += sizeof(topic.omega_los_ned);
	buf.offset += sizeof(topic.omega_los_ned);
	static_assert(sizeof(topic.velocity_sp) == 12, "size mismatch");
	memcpy(&topic.velocity_sp, buf.iterator, sizeof(topic.velocity_sp));
	buf.iterator += sizeof(topic.velocity_sp);
	buf.offset += sizeof(topic.velocity_sp);
	static_assert(sizeof(topic.acceleration_sp) == 12, "size mismatch");
	memcpy(&topic.acceleration_sp, buf.iterator, sizeof(topic.acceleration_sp));
	buf.iterator += sizeof(topic.acceleration_sp);
	buf.offset += sizeof(topic.acceleration_sp);
	static_assert(sizeof(topic.yaw_sp) == 4, "size mismatch");
	memcpy(&topic.yaw_sp, buf.iterator, sizeof(topic.yaw_sp));
	buf.iterator += sizeof(topic.yaw_sp);
	buf.offset += sizeof(topic.yaw_sp);
	static_assert(sizeof(topic.yaw_rate_sp) == 4, "size mismatch");
	memcpy(&topic.yaw_rate_sp, buf.iterator, sizeof(topic.yaw_rate_sp));
	buf.iterator += sizeof(topic.yaw_rate_sp);
	buf.offset += sizeof(topic.yaw_rate_sp);
	return true;
}
