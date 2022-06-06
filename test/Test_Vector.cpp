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

TEST(RotateZAxis, case1)
{
    Vector v1(0,1,0);
    Vector vOut = v1.RotateZAxis(35); // 35 clockwise
    EXPECT_NEAR(vOut.x, -0.574, 0.01);
    EXPECT_NEAR(vOut.y, 0.819 , 0.01);
    EXPECT_NEAR(vOut.z, 0, 0.01);
}

TEST(RotateZAxis, case2)
{
    Vector v1(5,3,1);
    Vector vOut = v1.RotateZAxis(-45); // 45 counter clockwise
    EXPECT_NEAR(vOut.x, 5.656, 0.01);
    EXPECT_NEAR(vOut.y, -1.414, 0.01);
    EXPECT_NEAR(vOut.z, 1, 0.01);
}

TEST(RotateYAxis, case1)
{
    Vector v1(0,0,1);
    Vector vOut = v1.RotateYAxis(35); // 35 clockwise
    EXPECT_NEAR(vOut.x, 0.574, 0.01);
    EXPECT_NEAR(vOut.y, 0, 0.01);
    EXPECT_NEAR(vOut.z, 0.819, 0.01);
}

TEST(RotateYAxis, case2)
{
    Vector v1(5,3,1);
    Vector vOut = v1.RotateYAxis(-45); // 45 counter clockwise
    EXPECT_NEAR(vOut.x, 2.828, 0.001);
    EXPECT_NEAR(vOut.y, 3, 0.001);  
    EXPECT_NEAR(vOut.z, 4.243, 0.001);
}

TEST(Reset, case1)
{
    Vector v1(2,3,4);
    v1.Reset();
    EXPECT_EQ(v1.x, 0);
    EXPECT_EQ(v1.y, 0);
    EXPECT_EQ(v1.z, 0);
}