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
#include <uORB/topics/dyt_status_reply.h>


static inline constexpr int ucdr_topic_size_dyt_status_reply()
{
	return 38;
}

static inline bool ucdr_serialize_dyt_status_reply(const void* data, ucdrBuffer& buf, int64_t time_offset = 0)
{
	const dyt_status_reply_s& topic = *static_cast<const dyt_status_reply_s*>(data);
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
	static_assert(sizeof(topic.control_code) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.control_code, sizeof(topic.control_code));
	buf.iterator += sizeof(topic.control_code);
	buf.offset += sizeof(topic.control_code);
	static_assert(sizeof(topic.param_length) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.param_length, sizeof(topic.param_length));
	buf.iterator += sizeof(topic.param_length);
	buf.offset += sizeof(topic.param_length);
	static_assert(sizeof(topic.truncated) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.truncated, sizeof(topic.truncated));
	buf.iterator += sizeof(topic.truncated);
	buf.offset += sizeof(topic.truncated);
	static_assert(sizeof(topic.params) == 16, "size mismatch");
	memcpy(buf.iterator, &topic.params, sizeof(topic.params));
	buf.iterator += sizeof(topic.params);
	buf.offset += sizeof(topic.params);
	buf.iterator += 1; // padding
	buf.offset += 1; // padding
	static_assert(sizeof(topic.parse_error_count) == 2, "size mismatch");
	memcpy(buf.iterator, &topic.parse_error_count, sizeof(topic.parse_error_count));
	buf.iterator += sizeof(topic.parse_error_count);
	buf.offset += sizeof(topic.parse_error_count);
	return true;
}

static inline bool ucdr_deserialize_dyt_status_reply(ucdrBuffer& buf, dyt_status_reply_s& topic, int64_t time_offset = 0)
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
	static_assert(sizeof(topic.control_code) == 1, "size mismatch");
	memcpy(&topic.control_code, buf.iterator, sizeof(topic.control_code));
	buf.iterator += sizeof(topic.control_code);
	buf.offset += sizeof(topic.control_code);
	static_assert(sizeof(topic.param_length) == 1, "size mismatch");
	memcpy(&topic.param_length, buf.iterator, sizeof(topic.param_length));
	buf.iterator += sizeof(topic.param_length);
	buf.offset += sizeof(topic.param_length);
	static_assert(sizeof(topic.truncated) == 1, "size mismatch");
	memcpy(&topic.truncated, buf.iterator, sizeof(topic.truncated));
	buf.iterator += sizeof(topic.truncated);
	buf.offset += sizeof(topic.truncated);
	static_assert(sizeof(topic.params) == 16, "size mismatch");
	memcpy(&topic.params, buf.iterator, sizeof(topic.params));
	buf.iterator += sizeof(topic.params);
	buf.offset += sizeof(topic.params);
	buf.iterator += 1; // padding
	buf.offset += 1; // padding
	static_assert(sizeof(topic.parse_error_count) == 2, "size mismatch");
	memcpy(&topic.parse_error_count, buf.iterator, sizeof(topic.parse_error_count));
	buf.iterator += sizeof(topic.parse_error_count);
	buf.offset += sizeof(topic.parse_error_count);
	return true;
}
