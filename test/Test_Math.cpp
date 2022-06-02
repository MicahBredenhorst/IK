#include <gtest/gtest.h>
#include <Math.h>
#include <Vector.h>
#include <iostream>

// https://github.com/google/googletest/blob/main/docs/reference/assertions.md#expect_near-expect_near

// https://www.calculatorsoup.com/calculators/algebra/dot-product-calculator.php
TEST(DotProduct, case1)
{
    Vector v1(1,2,3);
    Vector v2(1,2,3);
    double result = DotProduct(v1, v2);
    EXPECT_EQ(14, result);
}


TEST(DotProduct, case2)
{
    Vector v1 (2,3,3);
    Vector v2 (1,2,3);
    double result = DotProduct(v1, v2);
    EXPECT_EQ(17, result);
}

TEST(RadiansToDegree, case1)
{
    double radians = 1;
    double result = RadiansToDegree(radians);
    EXPECT_NEAR(57.295, result, 0.01);
}

// https://www.calculatorsoup.com/calculators/geometry-solids/distance-two-points.php
TEST(VectorSquaredDistance, case1)
{
    Vector v1 (12,15,2);
    Vector v2 (1,2,4);
    double result = VectorSquaredDistance(v1, v2);
    EXPECT_NEAR(294, result, 0.01);
}
