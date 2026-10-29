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
#include <uORB/topics/dyt_command.h>


static inline constexpr int ucdr_topic_size_dyt_command()
{
	return 60;
}

static inline bool ucdr_serialize_dyt_command(const void* data, ucdrBuffer& buf, int64_t time_offset = 0)
{
	const dyt_command_s& topic = *static_cast<const dyt_command_s*>(data);
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	const uint64_t timestamp_adjusted = topic.timestamp + time_offset;
	memcpy(buf.iterator, &timestamp_adjusted, sizeof(topic.timestamp));
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.command) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.command, sizeof(topic.command));
	buf.iterator += sizeof(topic.command);
	buf.offset += sizeof(topic.command);
	buf.iterator += 1; // padding
	buf.offset += 1; // padding
	static_assert(sizeof(topic.param_x) == 2, "size mismatch");
	memcpy(buf.iterator, &topic.param_x, sizeof(topic.param_x));
	buf.iterator += sizeof(topic.param_x);
	buf.offset += sizeof(topic.param_x);
	static_assert(sizeof(topic.param_y) == 2, "size mismatch");
	memcpy(buf.iterator, &topic.param_y, sizeof(topic.param_y));
	buf.iterator += sizeof(topic.param_y);
	buf.offset += sizeof(topic.param_y);
	static_assert(sizeof(topic.param3) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.param3, sizeof(topic.param3));
	buf.iterator += sizeof(topic.param3);
	buf.offset += sizeof(topic.param3);
	static_assert(sizeof(topic.zoom_rate) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.zoom_rate, sizeof(topic.zoom_rate));
	buf.iterator += sizeof(topic.zoom_rate);
	buf.offset += sizeof(topic.zoom_rate);
	static_assert(sizeof(topic.lat) == 8, "size mismatch");
	memcpy(buf.iterator, &topic.lat, sizeof(topic.lat));
	buf.iterator += sizeof(topic.lat);
	buf.offset += sizeof(topic.lat);
	static_assert(sizeof(topic.lon) == 8, "size mismatch");
	memcpy(buf.iterator, &topic.lon, sizeof(topic.lon));
	buf.iterator += sizeof(topic.lon);
	buf.offset += sizeof(topic.lon);
	static_assert(sizeof(topic.alt) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.alt, sizeof(topic.alt));
	buf.iterator += sizeof(topic.alt);
	buf.offset += sizeof(topic.alt);
	static_assert(sizeof(topic.rel_alt) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.rel_alt, sizeof(topic.rel_alt));
	buf.iterator += sizeof(topic.rel_alt);
	buf.offset += sizeof(topic.rel_alt);
	static_assert(sizeof(topic.roll_rad) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.roll_rad, sizeof(topic.roll_rad));
	buf.iterator += sizeof(topic.roll_rad);
	buf.offset += sizeof(topic.roll_rad);
	static_assert(sizeof(topic.pitch_rad) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.pitch_rad, sizeof(topic.pitch_rad));
	buf.iterator += sizeof(topic.pitch_rad);
	buf.offset += sizeof(topic.pitch_rad);
	static_assert(sizeof(topic.yaw_rad) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.yaw_rad, sizeof(topic.yaw_rad));
	buf.iterator += sizeof(topic.yaw_rad);
	buf.offset += sizeof(topic.yaw_rad);
	static_assert(sizeof(topic.airspeed_m_s) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.airspeed_m_s, sizeof(topic.airspeed_m_s));
	buf.iterator += sizeof(topic.airspeed_m_s);
	buf.offset += sizeof(topic.airspeed_m_s);
	static_assert(sizeof(topic.groundspeed_m_s) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.groundspeed_m_s, sizeof(topic.groundspeed_m_s));
	buf.iterator += sizeof(topic.groundspeed_m_s);
	buf.offset += sizeof(topic.groundspeed_m_s);
	return true;
}

static inline bool ucdr_deserialize_dyt_command(ucdrBuffer& buf, dyt_command_s& topic, int64_t time_offset = 0)
{
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	memcpy(&topic.timestamp, buf.iterator, sizeof(topic.timestamp));
	if (topic.timestamp == 0) topic.timestamp = hrt_absolute_time();
	else topic.timestamp = math::min(topic.timestamp - time_offset, hrt_absolute_time());
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.command) == 1, "size mismatch");
	memcpy(&topic.command, buf.iterator, sizeof(topic.command));
	buf.iterator += sizeof(topic.command);
	buf.offset += sizeof(topic.command);
	buf.iterator += 1; // padding
	buf.offset += 1; // padding
	static_assert(sizeof(topic.param_x) == 2, "size mismatch");
	memcpy(&topic.param_x, buf.iterator, sizeof(topic.param_x));
	buf.iterator += sizeof(topic.param_x);
	buf.offset += sizeof(topic.param_x);
	static_assert(sizeof(topic.param_y) == 2, "size mismatch");
	memcpy(&topic.param_y, buf.iterator, sizeof(topic.param_y));
	buf.iterator += sizeof(topic.param_y);
	buf.offset += sizeof(topic.param_y);
	static_assert(sizeof(topic.param3) == 1, "size mismatch");
	memcpy(&topic.param3, buf.iterator, sizeof(topic.param3));
	buf.iterator += sizeof(topic.param3);
	buf.offset += sizeof(topic.param3);
	static_assert(sizeof(topic.zoom_rate) == 1, "size mismatch");
	memcpy(&topic.zoom_rate, buf.iterator, sizeof(topic.zoom_rate));
	buf.iterator += sizeof(topic.zoom_rate);
	buf.offset += sizeof(topic.zoom_rate);
	static_assert(sizeof(topic.lat) == 8, "size mismatch");
	memcpy(&topic.lat, buf.iterator, sizeof(topic.lat));
	buf.iterator += sizeof(topic.lat);
	buf.offset += sizeof(topic.lat);
	static_assert(sizeof(topic.lon) == 8, "size mismatch");
	memcpy(&topic.lon, buf.iterator, sizeof(topic.lon));
	buf.iterator += sizeof(topic.lon);
	buf.offset += sizeof(topic.lon);
	static_assert(sizeof(topic.alt) == 4, "size mismatch");
	memcpy(&topic.alt, buf.iterator, sizeof(topic.alt));
	buf.iterator += sizeof(topic.alt);
	buf.offset += sizeof(topic.alt);
	static_assert(sizeof(topic.rel_alt) == 4, "size mismatch");
	memcpy(&topic.rel_alt, buf.iterator, sizeof(topic.rel_alt));
	buf.iterator += sizeof(topic.rel_alt);
	buf.offset += sizeof(topic.rel_alt);
	static_assert(sizeof(topic.roll_rad) == 4, "size mismatch");
	memcpy(&topic.roll_rad, buf.iterator, sizeof(topic.roll_rad));
	buf.iterator += sizeof(topic.roll_rad);
	buf.offset += sizeof(topic.roll_rad);
	static_assert(sizeof(topic.pitch_rad) == 4, "size mismatch");
	memcpy(&topic.pitch_rad, buf.iterator, sizeof(topic.pitch_rad));
	buf.iterator += sizeof(topic.pitch_rad);
	buf.offset += sizeof(topic.pitch_rad);
	static_assert(sizeof(topic.yaw_rad) == 4, "size mismatch");
	memcpy(&topic.yaw_rad, buf.iterator, sizeof(topic.yaw_rad));
	buf.iterator += sizeof(topic.yaw_rad);
	buf.offset += sizeof(topic.yaw_rad);
	static_assert(sizeof(topic.airspeed_m_s) == 4, "size mismatch");
	memcpy(&topic.airspeed_m_s, buf.iterator, sizeof(topic.airspeed_m_s));
	buf.iterator += sizeof(topic.airspeed_m_s);
	buf.offset += sizeof(topic.airspeed_m_s);
	static_assert(sizeof(topic.groundspeed_m_s) == 4, "size mismatch");
	memcpy(&topic.groundspeed_m_s, buf.iterator, sizeof(topic.groundspeed_m_s));
	buf.iterator += sizeof(topic.groundspeed_m_s);
	buf.offset += sizeof(topic.groundspeed_m_s);
	return true;
}
