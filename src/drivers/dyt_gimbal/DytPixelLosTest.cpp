/****************************************************************************
 *
 *   Copyright (c) 2026 PX4 Development Team. All rights reserved.
 *
 ****************************************************************************/

#include "DytPixelLos.hpp"

#include <gtest/gtest.h>

static constexpr float kPi = 3.14159265358979323846f;

TEST(DytPixelLos, DynamicFovCenterAndImageEdge)
{
	float los_x = NAN;
	float los_y = NAN;

	ASSERT_TRUE(dyt::pixelMissToLos(0, 0, 60.f, 1920, 1080, 0.f, los_x, los_y));
	EXPECT_FLOAT_EQ(los_x, 0.f);
	EXPECT_FLOAT_EQ(los_y, 0.f);

	ASSERT_TRUE(dyt::pixelMissToLos(960, 0, 60.f, 1920, 1080, 0.f, los_x, los_y));
	EXPECT_NEAR(los_x, kPi / 6.f, 1e-6f);
	EXPECT_FLOAT_EQ(los_y, 0.f);
}

TEST(DytPixelLos, ManualScaleOverride)
{
	float los_x = NAN;
	float los_y = NAN;

	ASSERT_TRUE(dyt::pixelMissToLos(20, -10, NAN, 1920, 1080, 0.05f, los_x, los_y));
	EXPECT_NEAR(los_x, kPi / 180.f, 1e-6f);
	EXPECT_NEAR(los_y, -kPi / 360.f, 1e-6f);
}

TEST(DytPixelLos, RejectsInvalidGeometryAndPixels)
{
	float los_x = 0.f;
	float los_y = 0.f;

	EXPECT_FALSE(dyt::pixelMissToLos(0, 0, NAN, 1920, 1080, 0.f, los_x, los_y));
	EXPECT_FALSE(dyt::pixelMissToLos(961, 0, 60.f, 1920, 1080, 0.f, los_x, los_y));
	EXPECT_FALSE(dyt::pixelMissToLos(0, 541, 60.f, 1920, 1080, 0.f, los_x, los_y));
	EXPECT_FALSE(dyt::pixelMissToLos(0, 0, 60.f, 0, 1080, 0.f, los_x, los_y));
}
