#include <gtest/gtest.h>
#include "Math.h"

TEST(Vector, CanInitializeVector)
{
    const Vector3 vector(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(1.0f, vector.getX());
    EXPECT_FLOAT_EQ(1.0f, vector.getX());
    EXPECT_FLOAT_EQ(1.0f, vector.getX());
}