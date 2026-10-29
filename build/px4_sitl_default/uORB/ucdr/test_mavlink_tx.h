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
#include <uORB/topics/test_mavlink_tx.h>


static inline constexpr int ucdr_topic_size_test_mavlink_tx()
{
	return 16;
}

static inline bool ucdr_serialize_test_mavlink_tx(const void* data, ucdrBuffer& buf, int64_t time_offset = 0)
{
	const test_mavlink_tx_s& topic = *static_cast<const test_mavlink_tx_s*>(data);
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	const uint64_t timestamp_adjusted = topic.timestamp + time_offset;
	memcpy(buf.iterator, &timestamp_adjusted, sizeof(topic.timestamp));
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.test1) == 1, "size mismatch");
	memcpy(buf.iterator, &topic.test1, sizeof(topic.test1));
	buf.iterator += sizeof(topic.test1);
	buf.offset += sizeof(topic.test1);
	buf.iterator += 1; // padding
	buf.offset += 1; // padding
	static_assert(sizeof(topic.test2) == 2, "size mismatch");
	memcpy(buf.iterator, &topic.test2, sizeof(topic.test2));
	buf.iterator += sizeof(topic.test2);
	buf.offset += sizeof(topic.test2);
	static_assert(sizeof(topic.test3) == 4, "size mismatch");
	memcpy(buf.iterator, &topic.test3, sizeof(topic.test3));
	buf.iterator += sizeof(topic.test3);
	buf.offset += sizeof(topic.test3);
	return true;
}

static inline bool ucdr_deserialize_test_mavlink_tx(ucdrBuffer& buf, test_mavlink_tx_s& topic, int64_t time_offset = 0)
{
	static_assert(sizeof(topic.timestamp) == 8, "size mismatch");
	memcpy(&topic.timestamp, buf.iterator, sizeof(topic.timestamp));
	if (topic.timestamp == 0) topic.timestamp = hrt_absolute_time();
	else topic.timestamp = math::min(topic.timestamp - time_offset, hrt_absolute_time());
	buf.iterator += sizeof(topic.timestamp);
	buf.offset += sizeof(topic.timestamp);
	static_assert(sizeof(topic.test1) == 1, "size mismatch");
	memcpy(&topic.test1, buf.iterator, sizeof(topic.test1));
	buf.iterator += sizeof(topic.test1);
	buf.offset += sizeof(topic.test1);
	buf.iterator += 1; // padding
	buf.offset += 1; // padding
	static_assert(sizeof(topic.test2) == 2, "size mismatch");
	memcpy(&topic.test2, buf.iterator, sizeof(topic.test2));
	buf.iterator += sizeof(topic.test2);
	buf.offset += sizeof(topic.test2);
	static_assert(sizeof(topic.test3) == 4, "size mismatch");
	memcpy(&topic.test3, buf.iterator, sizeof(topic.test3));
	buf.iterator += sizeof(topic.test3);
	buf.offset += sizeof(topic.test3);
	return true;
}
