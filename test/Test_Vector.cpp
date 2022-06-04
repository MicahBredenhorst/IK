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

TEST(Subtract, case1)
{
    Vector v1 (2,2,2);
    Vector v2 (1,0,1);
    Vector vResult = v1.Subtract(v2);
    EXPECT_EQ(vResult.x, 1);
    EXPECT_EQ(vResult.y, 2);
    EXPECT_EQ(vResult.z, 1);
}

TEST(Rotate, case1)
{
    Vector v1(0,1,0);
    Vector vOut = v1.Rotate(35);
    vOut.Print();
    EXPECT_NEAR(vOut.x, 0.700, 0.01);
    EXPECT_NEAR(vOut.y, 0.700, 0.01);
    EXPECT_NEAR(vOut.z, 0.700, 0.01);
}