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
#include <uORB/topics/swarm_mission_item.h>


static inline constexpr int ucdr_topic_size_swarm_mission_item()
{
	return 63;
}

static inline bool ucdr_serialize_swarm_mission_item(const void* data, ucdrBuffer& buf, int64_t time_offset = 0)
{
	const swarm_mission_item_s& topic = *static_cast<const swarm_mission_item_s*>(data);
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	const uint64_t timestamp_adjusted = topic.timestamp + time_offset;
	memcpy(buf.iterator, &timestamp_adjusted, sizeof(topic.timestamp));
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.group_id) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.group_id, sizeof(topic.group_id));
	buf.iterator += sizeof(topic.group_id);
	buf.offset += sizeof(topic.group_id);
	static_assert(sizeof(topic.leader_id) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.leader_id, sizeof(topic.leader_id));
	buf.iterator += sizeof(topic.leader_id);
	buf.offset += sizeof(topic.leader_id);
	buf.iterator += 2; // padding
	buf.offset += 2; // padding
	static_assert(sizeof(topic.mission_id) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.mission_id, sizeof(topic.mission_id));
	buf.iterator += sizeof(topic.mission_id);
	buf.offset += sizeof(topic.mission_id);
	static_assert(sizeof(topic.total_count) == 2, "size mismatch");
	memcpy(buf.iterator, &topic.total_count, sizeof(topic.total_count));
	buf.iterator += sizeof(topic.total_count);
	buf.offset += sizeof(topic.total_count);
	static_assert(sizeof(topic.current_seq) == 2, "size mismatch");
	memcpy(buf.iterator, &topic.current_seq, sizeof(topic.current_seq));
	buf.iterator += sizeof(topic.current_seq);
	buf.offset += sizeof(topic.current_seq);
	static_assert(sizeof(topic.seq) == 2, "size mismatch");
	memcpy(buf.iterator, &topic.seq, sizeof(topic.seq));
	buf.iterator += sizeof(topic.seq);
	buf.offset += sizeof(topic.seq);
	static_assert(sizeof(topic.nav_cmd) == 2, "size mismatch");
	memcpy(buf.iterator, &topic.nav_cmd, sizeof(topic.nav_cmd));
	buf.iterator += sizeof(topic.nav_cmd);
	buf.offset += sizeof(topic.nav_cmd);
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
	static_assert(sizeof(topic.yaw) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.yaw, sizeof(topic.yaw));
	buf.iterator += sizeof(topic.yaw);
	buf.offset += sizeof(topic.yaw);
	static_assert(sizeof(topic.acceptance_radius) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.acceptance_radius, sizeof(topic.acceptance_radius));
	buf.iterator += sizeof(topic.acceptance_radius);
	buf.offset += sizeof(topic.acceptance_radius);
	static_assert(sizeof(topic.loiter_radius) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.loiter_radius, sizeof(topic.loiter_radius));
	buf.iterator += sizeof(topic.loiter_radius);
	buf.offset += sizeof(topic.loiter_radius);
	static_assert(sizeof(topic.time_inside) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.time_inside, sizeof(topic.time_inside));
	buf.iterator += sizeof(topic.time_inside);
	buf.offset += sizeof(topic.time_inside);
	static_assert(sizeof(topic.autocontinue) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.autocontinue, sizeof(topic.autocontinue));
	buf.iterator += sizeof(topic.autocontinue);
	buf.offset += sizeof(topic.autocontinue);
	static_assert(sizeof(topic.sync_type) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.sync_type, sizeof(topic.sync_type));
	buf.iterator += sizeof(topic.sync_type);
	buf.offset += sizeof(topic.sync_type);
	static_assert(sizeof(topic.is_relay) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.is_relay, sizeof(topic.is_relay));
	buf.iterator += sizeof(topic.is_relay);
	buf.offset += sizeof(topic.is_relay);
	return true;
}

static inline bool ucdr_deserialize_swarm_mission_item(ucdrBuffer& buf, swarm_mission_item_s& topic, int64_t time_offset = 0)
{
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	memcpy(&topic.timestamp, buf.iterator, sizeof(topic.timestamp));
	if (topic.timestamp == 0) topic.timestamp = hrt_absolute_time();
	else topic.timestamp = math::min(topic.timestamp - time_offset, hrt_absolute_time());
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.group_id) == 1, "size mismatch");
	memcpy(&topic.group_id, buf.iterator, sizeof(topic.group_id));
	buf.iterator += sizeof(topic.group_id);
	buf.offset += sizeof(topic.group_id);
	static_assert(sizeof(topic.leader_id) == 1, "size mismatch");
	memcpy(&topic.leader_id, buf.iterator, sizeof(topic.leader_id));
	buf.iterator += sizeof(topic.leader_id);
	buf.offset += sizeof(topic.leader_id);
	buf.iterator += 2; // padding
	buf.offset += 2; // padding
	static_assert(sizeof(topic.mission_id) == 4, "size mismatch");
	memcpy(&topic.mission_id, buf.iterator, sizeof(topic.mission_id));
	buf.iterator += sizeof(topic.mission_id);
	buf.offset += sizeof(topic.mission_id);
	static_assert(sizeof(topic.total_count) == 2, "size mismatch");
	memcpy(&topic.total_count, buf.iterator, sizeof(topic.total_count));
	buf.iterator += sizeof(topic.total_count);
	buf.offset += sizeof(topic.total_count);
	static_assert(sizeof(topic.current_seq) == 2, "size mismatch");
	memcpy(&topic.current_seq, buf.iterator, sizeof(topic.current_seq));
	buf.iterator += sizeof(topic.current_seq);
	buf.offset += sizeof(topic.current_seq);
	static_assert(sizeof(topic.seq) == 2, "size mismatch");
	memcpy(&topic.seq, buf.iterator, sizeof(topic.seq));
	buf.iterator += sizeof(topic.seq);
	buf.offset += sizeof(topic.seq);
	static_assert(sizeof(topic.nav_cmd) == 2, "size mismatch");
	memcpy(&topic.nav_cmd, buf.iterator, sizeof(topic.nav_cmd));
	buf.iterator += sizeof(topic.nav_cmd);
	buf.offset += sizeof(topic.nav_cmd);
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
	static_assert(sizeof(topic.yaw) == 4, "size mismatch");
	memcpy(&topic.yaw, buf.iterator, sizeof(topic.yaw));
	buf.iterator += sizeof(topic.yaw);
	buf.offset += sizeof(topic.yaw);
	static_assert(sizeof(topic.acceptance_radius) == 4, "size mismatch");
	memcpy(&topic.acceptance_radius, buf.iterator, sizeof(topic.acceptance_radius));
	buf.iterator += sizeof(topic.acceptance_radius);
	buf.offset += sizeof(topic.acceptance_radius);
	static_assert(sizeof(topic.loiter_radius) == 4, "size mismatch");
	memcpy(&topic.loiter_radius, buf.iterator, sizeof(topic.loiter_radius));
	buf.iterator += sizeof(topic.loiter_radius);
	buf.offset += sizeof(topic.loiter_radius);
	static_assert(sizeof(topic.time_inside) == 4, "size mismatch");
	memcpy(&topic.time_inside, buf.iterator, sizeof(topic.time_inside));
	buf.iterator += sizeof(topic.time_inside);
	buf.offset += sizeof(topic.time_inside);
	static_assert(sizeof(topic.autocontinue) == 1, "size mismatch");
	memcpy(&topic.autocontinue, buf.iterator, sizeof(topic.autocontinue));
	buf.iterator += sizeof(topic.autocontinue);
	buf.offset += sizeof(topic.autocontinue);
	static_assert(sizeof(topic.sync_type) == 1, "size mismatch");
	memcpy(&topic.sync_type, buf.iterator, sizeof(topic.sync_type));
	buf.iterator += sizeof(topic.sync_type);
	buf.offset += sizeof(topic.sync_type);
	static_assert(sizeof(topic.is_relay) == 1, "size mismatch");
	memcpy(&topic.is_relay, buf.iterator, sizeof(topic.is_relay));
	buf.iterator += sizeof(topic.is_relay);
	buf.offset += sizeof(topic.is_relay);
	return true;
}
