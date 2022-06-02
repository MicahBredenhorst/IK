#include <gtest/gtest.h>
#include <Vector.h>

TEST(Normalize, case1)
{
    Vector v1 (1,2,3);
    v1.Normalize();
    EXPECT_NEAR(v1.x, 0.267, 0.01);
    EXPECT_NEAR(v1.y, 0.534, 0.01);
    EXPECT_NEAR(v1.z, 0.801, 0.01);
}