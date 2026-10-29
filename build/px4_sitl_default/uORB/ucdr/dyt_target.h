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
#include <uORB/topics/dyt_target.h>


static inline constexpr int ucdr_topic_size_dyt_target()
{
	return 98;
}

static inline bool ucdr_serialize_dyt_target(const void* data, ucdrBuffer& buf, int64_t time_offset = 0)
{
	const dyt_target_s& topic = *static_cast<const dyt_target_s*>(data);
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	const uint64_t timestamp_adjusted = topic.timestamp + time_offset;
	memcpy(buf.iterator, &timestamp_adjusted, sizeof(topic.timestamp));
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.timestamp_sample) == 8, "size mismatch");
	const uint64_t timestamp_sample_adjusted = topic.timestamp_sample + time_offset;
	memcpy(buf.iterator, &timestamp_sample_adjusted, sizeof(topic.timestamp_sample));
	buf.iterator += sizeof(topic.timestamp_sample);
	buf.offset += sizeof(topic.timestamp_sample);
	static_assert(sizeof(topic.frame_counter) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.frame_counter, sizeof(topic.frame_counter));
	buf.iterator += sizeof(topic.frame_counter);
	buf.offset += sizeof(topic.frame_counter);
	static_assert(sizeof(topic.tracking_state) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.tracking_state, sizeof(topic.tracking_state));
	buf.iterator += sizeof(topic.tracking_state);
	buf.offset += sizeof(topic.tracking_state);
	static_assert(sizeof(topic.video_source) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.video_source, sizeof(topic.video_source));
	buf.iterator += sizeof(topic.video_source);
	buf.offset += sizeof(topic.video_source);
	static_assert(sizeof(topic.tracking_algorithm) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.tracking_algorithm, sizeof(topic.tracking_algorithm));
	buf.iterator += sizeof(topic.tracking_algorithm);
	buf.offset += sizeof(topic.tracking_algorithm);
	static_assert(sizeof(topic.target_valid) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.target_valid, sizeof(topic.target_valid));
	buf.iterator += sizeof(topic.target_valid);
	buf.offset += sizeof(topic.target_valid);
	static_assert(sizeof(topic.auto_hint) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.auto_hint, sizeof(topic.auto_hint));
	buf.iterator += sizeof(topic.auto_hint);
	buf.offset += sizeof(topic.auto_hint);
	static_assert(sizeof(topic.image_enhance) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.image_enhance, sizeof(topic.image_enhance));
	buf.iterator += sizeof(topic.image_enhance);
	buf.offset += sizeof(topic.image_enhance);
	static_assert(sizeof(topic.recording) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.recording, sizeof(topic.recording));
	buf.iterator += sizeof(topic.recording);
	buf.offset += sizeof(topic.recording);
	static_assert(sizeof(topic.motor_on) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.motor_on, sizeof(topic.motor_on));
	buf.iterator += sizeof(topic.motor_on);
	buf.offset += sizeof(topic.motor_on);
	static_assert(sizeof(topic.follow_mode) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.follow_mode, sizeof(topic.follow_mode));
	buf.iterator += sizeof(topic.follow_mode);
	buf.offset += sizeof(topic.follow_mode);
	static_assert(sizeof(topic.laser_on) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.laser_on, sizeof(topic.laser_on));
	buf.iterator += sizeof(topic.laser_on);
	buf.offset += sizeof(topic.laser_on);
	static_assert(sizeof(topic.selftest_done) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.selftest_done, sizeof(topic.selftest_done));
	buf.iterator += sizeof(topic.selftest_done);
	buf.offset += sizeof(topic.selftest_done);
	static_assert(sizeof(topic.gyro_calib_failed) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.gyro_calib_failed, sizeof(topic.gyro_calib_failed));
	buf.iterator += sizeof(topic.gyro_calib_failed);
	buf.offset += sizeof(topic.gyro_calib_failed);
	static_assert(sizeof(topic.servo_fault) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.servo_fault, sizeof(topic.servo_fault));
	buf.iterator += sizeof(topic.servo_fault);
	buf.offset += sizeof(topic.servo_fault);
	static_assert(sizeof(topic.image_board_fault) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.image_board_fault, sizeof(topic.image_board_fault));
	buf.iterator += sizeof(topic.image_board_fault);
	buf.offset += sizeof(topic.image_board_fault);
	buf.iterator += 2; // padding
	buf.offset += 2; // padding
	static_assert(sizeof(topic.los_x_rad) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.los_x_rad, sizeof(topic.los_x_rad));
	buf.iterator += sizeof(topic.los_x_rad);
	buf.offset += sizeof(topic.los_x_rad);
	static_assert(sizeof(topic.los_y_rad) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.los_y_rad, sizeof(topic.los_y_rad));
	buf.iterator += sizeof(topic.los_y_rad);
	buf.offset += sizeof(topic.los_y_rad);
	static_assert(sizeof(topic.gimbal_roll_rad) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.gimbal_roll_rad, sizeof(topic.gimbal_roll_rad));
	buf.iterator += sizeof(topic.gimbal_roll_rad);
	buf.offset += sizeof(topic.gimbal_roll_rad);
	static_assert(sizeof(topic.gimbal_pitch_rad) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.gimbal_pitch_rad, sizeof(topic.gimbal_pitch_rad));
	buf.iterator += sizeof(topic.gimbal_pitch_rad);
	buf.offset += sizeof(topic.gimbal_pitch_rad);
	static_assert(sizeof(topic.gimbal_yaw_rad) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.gimbal_yaw_rad, sizeof(topic.gimbal_yaw_rad));
	buf.iterator += sizeof(topic.gimbal_yaw_rad);
	buf.offset += sizeof(topic.gimbal_yaw_rad);
	static_assert(sizeof(topic.gimbal_roll_rate_rad_s) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.gimbal_roll_rate_rad_s, sizeof(topic.gimbal_roll_rate_rad_s));
	buf.iterator += sizeof(topic.gimbal_roll_rate_rad_s);
	buf.offset += sizeof(topic.gimbal_roll_rate_rad_s);
	static_assert(sizeof(topic.gimbal_pitch_rate_rad_s) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.gimbal_pitch_rate_rad_s, sizeof(topic.gimbal_pitch_rate_rad_s));
	buf.iterator += sizeof(topic.gimbal_pitch_rate_rad_s);
	buf.offset += sizeof(topic.gimbal_pitch_rate_rad_s);
	static_assert(sizeof(topic.gimbal_yaw_rate_rad_s) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.gimbal_yaw_rate_rad_s, sizeof(topic.gimbal_yaw_rate_rad_s));
	buf.iterator += sizeof(topic.gimbal_yaw_rate_rad_s);
	buf.offset += sizeof(topic.gimbal_yaw_rate_rad_s);
	static_assert(sizeof(topic.bbox_width_px) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.bbox_width_px, sizeof(topic.bbox_width_px));
	buf.iterator += sizeof(topic.bbox_width_px);
	buf.offset += sizeof(topic.bbox_width_px);
	static_assert(sizeof(topic.bbox_height_px) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.bbox_height_px, sizeof(topic.bbox_height_px));
	buf.iterator += sizeof(topic.bbox_height_px);
	buf.offset += sizeof(topic.bbox_height_px);
	static_assert(sizeof(topic.range_m) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.range_m, sizeof(topic.range_m));
	buf.iterator += sizeof(topic.range_m);
	buf.offset += sizeof(topic.range_m);
	static_assert(sizeof(topic.zoom_ratio) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.zoom_ratio, sizeof(topic.zoom_ratio));
	buf.iterator += sizeof(topic.zoom_ratio);
	buf.offset += sizeof(topic.zoom_ratio);
	static_assert(sizeof(topic.frame_dt_s) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.frame_dt_s, sizeof(topic.frame_dt_s));
	buf.iterator += sizeof(topic.frame_dt_s);
	buf.offset += sizeof(topic.frame_dt_s);
	static_assert(sizeof(topic.last_rx_age_s) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.last_rx_age_s, sizeof(topic.last_rx_age_s));
	buf.iterator += sizeof(topic.last_rx_age_s);
	buf.offset += sizeof(topic.last_rx_age_s);
	static_assert(sizeof(topic.parse_error_count) == 2, "size mismatch");
	memcpy(buf.iterator, &topic.parse_error_count, sizeof(topic.parse_error_count));
	buf.iterator += sizeof(topic.parse_error_count);
	buf.offset += sizeof(topic.parse_error_count);
	static_assert(sizeof(topic.status1) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.status1, sizeof(topic.status1));
	buf.iterator += sizeof(topic.status1);
	buf.offset += sizeof(topic.status1);
	static_assert(sizeof(topic.status2) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.status2, sizeof(topic.status2));
	buf.iterator += sizeof(topic.status2);
	buf.offset += sizeof(topic.status2);
	static_assert(sizeof(topic.status3) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.status3, sizeof(topic.status3));
	buf.iterator += sizeof(topic.status3);
	buf.offset += sizeof(topic.status3);
	static_assert(sizeof(topic.self_test_raw) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.self_test_raw, sizeof(topic.self_test_raw));
	buf.iterator += sizeof(topic.self_test_raw);
	buf.offset += sizeof(topic.self_test_raw);
	return true;
}

static inline bool ucdr_deserialize_dyt_target(ucdrBuffer& buf, dyt_target_s& topic, int64_t time_offset = 0)
{
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	memcpy(&topic.timestamp, buf.iterator, sizeof(topic.timestamp));
	if (topic.timestamp == 0) topic.timestamp = hrt_absolute_time();
	else topic.timestamp = math::min(topic.timestamp - time_offset, hrt_absolute_time());
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.timestamp_sample) == 8, "size mismatch");
	memcpy(&topic.timestamp_sample, buf.iterator, sizeof(topic.timestamp_sample));
	if (topic.timestamp_sample == 0) topic.timestamp_sample = hrt_absolute_time();
	else topic.timestamp_sample = math::min(topic.timestamp_sample - time_offset, hrt_absolute_time());
	buf.iterator += sizeof(topic.timestamp_sample);
	buf.offset += sizeof(topic.timestamp_sample);
	static_assert(sizeof(topic.frame_counter) == 4, "size mismatch");
	memcpy(&topic.frame_counter, buf.iterator, sizeof(topic.frame_counter));
	buf.iterator += sizeof(topic.frame_counter);
	buf.offset += sizeof(topic.frame_counter);
	static_assert(sizeof(topic.tracking_state) == 1, "size mismatch");
	memcpy(&topic.tracking_state, buf.iterator, sizeof(topic.tracking_state));
	buf.iterator += sizeof(topic.tracking_state);
	buf.offset += sizeof(topic.tracking_state);
	static_assert(sizeof(topic.video_source) == 1, "size mismatch");
	memcpy(&topic.video_source, buf.iterator, sizeof(topic.video_source));
	buf.iterator += sizeof(topic.video_source);
	buf.offset += sizeof(topic.video_source);
	static_assert(sizeof(topic.tracking_algorithm) == 1, "size mismatch");
	memcpy(&topic.tracking_algorithm, buf.iterator, sizeof(topic.tracking_algorithm));
	buf.iterator += sizeof(topic.tracking_algorithm);
	buf.offset += sizeof(topic.tracking_algorithm);
	static_assert(sizeof(topic.target_valid) == 1, "size mismatch");
	memcpy(&topic.target_valid, buf.iterator, sizeof(topic.target_valid));
	buf.iterator += sizeof(topic.target_valid);
	buf.offset += sizeof(topic.target_valid);
	static_assert(sizeof(topic.auto_hint) == 1, "size mismatch");
	memcpy(&topic.auto_hint, buf.iterator, sizeof(topic.auto_hint));
	buf.iterator += sizeof(topic.auto_hint);
	buf.offset += sizeof(topic.auto_hint);
	static_assert(sizeof(topic.image_enhance) == 1, "size mismatch");
	memcpy(&topic.image_enhance, buf.iterator, sizeof(topic.image_enhance));
	buf.iterator += sizeof(topic.image_enhance);
	buf.offset += sizeof(topic.image_enhance);
	static_assert(sizeof(topic.recording) == 1, "size mismatch");
	memcpy(&topic.recording, buf.iterator, sizeof(topic.recording));
	buf.iterator += sizeof(topic.recording);
	buf.offset += sizeof(topic.recording);
	static_assert(sizeof(topic.motor_on) == 1, "size mismatch");
	memcpy(&topic.motor_on, buf.iterator, sizeof(topic.motor_on));
	buf.iterator += sizeof(topic.motor_on);
	buf.offset += sizeof(topic.motor_on);
	static_assert(sizeof(topic.follow_mode) == 1, "size mismatch");
	memcpy(&topic.follow_mode, buf.iterator, sizeof(topic.follow_mode));
	buf.iterator += sizeof(topic.follow_mode);
	buf.offset += sizeof(topic.follow_mode);
	static_assert(sizeof(topic.laser_on) == 1, "size mismatch");
	memcpy(&topic.laser_on, buf.iterator, sizeof(topic.laser_on));
	buf.iterator += sizeof(topic.laser_on);
	buf.offset += sizeof(topic.laser_on);
	static_assert(sizeof(topic.selftest_done) == 1, "size mismatch");
	memcpy(&topic.selftest_done, buf.iterator, sizeof(topic.selftest_done));
	buf.iterator += sizeof(topic.selftest_done);
	buf.offset += sizeof(topic.selftest_done);
	static_assert(sizeof(topic.gyro_calib_failed) == 1, "size mismatch");
	memcpy(&topic.gyro_calib_failed, buf.iterator, sizeof(topic.gyro_calib_failed));
	buf.iterator += sizeof(topic.gyro_calib_failed);
	buf.offset += sizeof(topic.gyro_calib_failed);
	static_assert(sizeof(topic.servo_fault) == 1, "size mismatch");
	memcpy(&topic.servo_fault, buf.iterator, sizeof(topic.servo_fault));
	buf.iterator += sizeof(topic.servo_fault);
	buf.offset += sizeof(topic.servo_fault);
	static_assert(sizeof(topic.image_board_fault) == 1, "size mismatch");
	memcpy(&topic.image_board_fault, buf.iterator, sizeof(topic.image_board_fault));
	buf.iterator += sizeof(topic.image_board_fault);
	buf.offset += sizeof(topic.image_board_fault);
	buf.iterator += 2; // padding
	buf.offset += 2; // padding
	static_assert(sizeof(topic.los_x_rad) == 4, "size mismatch");
	memcpy(&topic.los_x_rad, buf.iterator, sizeof(topic.los_x_rad));
	buf.iterator += sizeof(topic.los_x_rad);
	buf.offset += sizeof(topic.los_x_rad);
	static_assert(sizeof(topic.los_y_rad) == 4, "size mismatch");
	memcpy(&topic.los_y_rad, buf.iterator, sizeof(topic.los_y_rad));
	buf.iterator += sizeof(topic.los_y_rad);
	buf.offset += sizeof(topic.los_y_rad);
	static_assert(sizeof(topic.gimbal_roll_rad) == 4, "size mismatch");
	memcpy(&topic.gimbal_roll_rad, buf.iterator, sizeof(topic.gimbal_roll_rad));
	buf.iterator += sizeof(topic.gimbal_roll_rad);
	buf.offset += sizeof(topic.gimbal_roll_rad);
	static_assert(sizeof(topic.gimbal_pitch_rad) == 4, "size mismatch");
	memcpy(&topic.gimbal_pitch_rad, buf.iterator, sizeof(topic.gimbal_pitch_rad));
	buf.iterator += sizeof(topic.gimbal_pitch_rad);
	buf.offset += sizeof(topic.gimbal_pitch_rad);
	static_assert(sizeof(topic.gimbal_yaw_rad) == 4, "size mismatch");
	memcpy(&topic.gimbal_yaw_rad, buf.iterator, sizeof(topic.gimbal_yaw_rad));
	buf.iterator += sizeof(topic.gimbal_yaw_rad);
	buf.offset += sizeof(topic.gimbal_yaw_rad);
	static_assert(sizeof(topic.gimbal_roll_rate_rad_s) == 4, "size mismatch");
	memcpy(&topic.gimbal_roll_rate_rad_s, buf.iterator, sizeof(topic.gimbal_roll_rate_rad_s));
	buf.iterator += sizeof(topic.gimbal_roll_rate_rad_s);
	buf.offset += sizeof(topic.gimbal_roll_rate_rad_s);
	static_assert(sizeof(topic.gimbal_pitch_rate_rad_s) == 4, "size mismatch");
	memcpy(&topic.gimbal_pitch_rate_rad_s, buf.iterator, sizeof(topic.gimbal_pitch_rate_rad_s));
	buf.iterator += sizeof(topic.gimbal_pitch_rate_rad_s);
	buf.offset += sizeof(topic.gimbal_pitch_rate_rad_s);
	static_assert(sizeof(topic.gimbal_yaw_rate_rad_s) == 4, "size mismatch");
	memcpy(&topic.gimbal_yaw_rate_rad_s, buf.iterator, sizeof(topic.gimbal_yaw_rate_rad_s));
	buf.iterator += sizeof(topic.gimbal_yaw_rate_rad_s);
	buf.offset += sizeof(topic.gimbal_yaw_rate_rad_s);
	static_assert(sizeof(topic.bbox_width_px) == 4, "size mismatch");
	memcpy(&topic.bbox_width_px, buf.iterator, sizeof(topic.bbox_width_px));
	buf.iterator += sizeof(topic.bbox_width_px);
	buf.offset += sizeof(topic.bbox_width_px);
	static_assert(sizeof(topic.bbox_height_px) == 4, "size mismatch");
	memcpy(&topic.bbox_height_px, buf.iterator, sizeof(topic.bbox_height_px));
	buf.iterator += sizeof(topic.bbox_height_px);
	buf.offset += sizeof(topic.bbox_height_px);
	static_assert(sizeof(topic.range_m) == 4, "size mismatch");
	memcpy(&topic.range_m, buf.iterator, sizeof(topic.range_m));
	buf.iterator += sizeof(topic.range_m);
	buf.offset += sizeof(topic.range_m);
	static_assert(sizeof(topic.zoom_ratio) == 4, "size mismatch");
	memcpy(&topic.zoom_ratio, buf.iterator, sizeof(topic.zoom_ratio));
	buf.iterator += sizeof(topic.zoom_ratio);
	buf.offset += sizeof(topic.zoom_ratio);
	static_assert(sizeof(topic.frame_dt_s) == 4, "size mismatch");
	memcpy(&topic.frame_dt_s, buf.iterator, sizeof(topic.frame_dt_s));
	buf.iterator += sizeof(topic.frame_dt_s);
	buf.offset += sizeof(topic.frame_dt_s);
	static_assert(sizeof(topic.last_rx_age_s) == 4, "size mismatch");
	memcpy(&topic.last_rx_age_s, buf.iterator, sizeof(topic.last_rx_age_s));
	buf.iterator += sizeof(topic.last_rx_age_s);
	buf.offset += sizeof(topic.last_rx_age_s);
	static_assert(sizeof(topic.parse_error_count) == 2, "size mismatch");
	memcpy(&topic.parse_error_count, buf.iterator, sizeof(topic.parse_error_count));
	buf.iterator += sizeof(topic.parse_error_count);
	buf.offset += sizeof(topic.parse_error_count);
	static_assert(sizeof(topic.status1) == 1, "size mismatch");
	memcpy(&topic.status1, buf.iterator, sizeof(topic.status1));
	buf.iterator += sizeof(topic.status1);
	buf.offset += sizeof(topic.status1);
	static_assert(sizeof(topic.status2) == 1, "size mismatch");
	memcpy(&topic.status2, buf.iterator, sizeof(topic.status2));
	buf.iterator += sizeof(topic.status2);
	buf.offset += sizeof(topic.status2);
	static_assert(sizeof(topic.status3) == 1, "size mismatch");
	memcpy(&topic.status3, buf.iterator, sizeof(topic.status3));
	buf.iterator += sizeof(topic.status3);
	buf.offset += sizeof(topic.status3);
	static_assert(sizeof(topic.self_test_raw) == 1, "size mismatch");
	memcpy(&topic.self_test_raw, buf.iterator, sizeof(topic.self_test_raw));
	buf.iterator += sizeof(topic.self_test_raw);
	buf.offset += sizeof(topic.self_test_raw);
	return true;
}
