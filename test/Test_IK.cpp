#include <gtest/gtest.h>
#include <IK.h>
#include <iostream>

TEST(dampRotation, case1)
{
    double turnDeg = 20;
    Link link(Vector(0,0,0), Vector(0,0,0), 0, 0, 10.0);
    dampRotation(&turnDeg, &link);
    EXPECT_EQ(turnDeg, 10);
}

TEST(dampRotation, case2)
{
    double turnDeg = 9;
    Link link(Vector(0,0,0), Vector(0,0,0), 0, 0, 10.0);
    dampRotation(&turnDeg, &link);
    EXPECT_EQ(turnDeg, 9);
}

TEST(restrictRotation, case1)
{
    Link link(Vector(0,0,0), Vector(30,0,0), 20, 0, 0);
    Rotation direction = Rotation::clockwise;
    restrictRotation(&link.rot.x, link, direction);
    EXPECT_EQ(link.rot.x, 20); 
}

TEST(restrictRotation, case2)
{
    Link link(Vector(0,0,0), Vector(10,0,0), 0, 20, 0);
    Rotation direction = Rotation::counterClockwise;
    restrictRotation(&link.rot.x, link, direction);
    EXPECT_EQ(link.rot.x, 20); 
}


TEST(restrictRotation, case3)
{
    Link link(Vector(0,0,0), Vector(10,0,0), 20, 0, 0);
    Rotation direction = Rotation::clockwise;
    restrictRotation(&link.rot.x, link, direction);
    EXPECT_EQ(link.rot.x, 10); 
}

TEST(getRotationDirection, case1)
{
    double crossProduct = 0.1;
    EXPECT_EQ(Rotation::clockwise, getRotationDirection(crossProduct));
}

TEST(getRotationDirection, case2)
{
    double crossProduct = -0.1;
    EXPECT_EQ(Rotation::counterClockwise, getRotationDirection(crossProduct));
}

// TODO: first fix RotateZAxis and RotateYAxis.

// TEST(applyRotation, case1)
// {
//     Link* armPrevious[2];
//     arm[0] = Link(Vector(0,0,0), Vector(0,0,0));
//     arm[1] = Link(Vector(0,0,0), Vector(0,0,0));


//     Link* arm[2];
//     arm[0] = Link(Vector(0,0,0), Vector(0,0,0));
//     arm[1] = Link(Vector(0,0,0), Vector(0,0,0));

//     applyRotation(&arm, &armPrevious);

//     EXPECT_EQ();
// }