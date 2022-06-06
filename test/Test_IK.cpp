#include <gtest/gtest.h>
#include <IK.h>
#include <Math.h>
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

TEST(dampRotation, case3)
{
    double turnDeg = -9;
    Link link(Vector(0,0,0), Vector(0,0,0), 0, 0, 8);
    dampRotation(&turnDeg, &link);
    EXPECT_EQ(turnDeg, -8);
}



// max, min
TEST(restrictRotation, case1)
{
    Link link(Vector(0,0,0), Vector(30,0,0), 20, 0, 0);
    restrictRotation(&link.rot.x, link);
    EXPECT_EQ(link.rot.x, 20); 
}

// max, min
TEST(restrictRotation, case2)
{
    Link link(Vector(0,0,0), Vector(19,0,0), 40, 20, 0);
    restrictRotation(&link.rot.x, link);
    EXPECT_EQ(link.rot.x, 19); 
}


TEST(restrictRotation, case3)
{
    Link link(Vector(0,0,0), Vector(10,0,0), 20, 0, 0);
    restrictRotation(&link.rot.x, link);
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

//TURN ON Z axis
TEST(forwardsKinematics, case1)
{
    Link arm[3];
    arm[0] = Link(2, Vector(0,0,0));
    arm[1] = Link(2, Vector(0,0,0));
    arm[2] = Link(2, Vector(0,0,0)); 
    forwardsKinematics(arm, 3);

    EXPECT_EQ(arm[1].loc.x, 2);
    EXPECT_EQ(arm[2].loc.x, 4);
}

// TURN ON Z axis
TEST(forwardsKinematics, case2)
{
    Link arm[3];
    arm[0] = Link(2, Vector(0,0,0));
    arm[1] = Link(2, Vector(0,0,90));
    arm[2] = Link(2, Vector(0,0,0)); 
    forwardsKinematics(arm, 3);

    EXPECT_EQ(arm[1].loc.x, 2);
    EXPECT_EQ(arm[1].loc.y, 0);
    EXPECT_EQ(arm[1].loc.z, 0);

    EXPECT_EQ(arm[2].loc.x, 2);
    EXPECT_EQ(arm[2].loc.y, 2);
    EXPECT_EQ(arm[2].loc.z, 0);
}

// TURN ON Y axis
TEST(forwardsKinematics, case3)
{
    Link arm[3];
    arm[0] = Link(2, Vector(0,-90,0));
    arm[1] = Link(2, Vector(0,0,0));
    arm[2] = Link(2, Vector(0,0,0)); 
    forwardsKinematics(arm, 3);

    EXPECT_EQ(arm[1].loc.x, 0);
    EXPECT_EQ(arm[1].loc.y, 0);
    EXPECT_EQ(arm[1].loc.z, -2);

    EXPECT_EQ(arm[2].loc.x, 0);
    EXPECT_EQ(arm[2].loc.y, 0);
    EXPECT_EQ(arm[2].loc.z, -4);
}

// TURN ON Z and Y axis
TEST(forwardsKinematics, case4)
{
    Link arm[5];
    arm[0] = Link(2, Vector(0,0,0));
    arm[1] = Link(2, Vector(0,-90,0));
    arm[2] = Link(2, Vector(0,-90,0));
    arm[3] = Link(2, Vector(0,0, 90));
    arm[4] = Link(2, Vector(0,0,0));

    forwardsKinematics(arm, 5);

    EXPECT_EQ(arm[0].loc.x, 0);
    EXPECT_EQ(arm[0].loc.y, 0);
    EXPECT_EQ(arm[0].loc.z, 0);

    EXPECT_EQ(arm[1].loc.x, 2);
    EXPECT_EQ(arm[1].loc.y, 0);
    EXPECT_EQ(arm[1].loc.z, 0);

    EXPECT_EQ(arm[2].loc.x, 2);
    EXPECT_EQ(arm[2].loc.y, 0);
    EXPECT_EQ(arm[2].loc.z, -2);

    EXPECT_EQ(arm[3].loc.x, 0);
    EXPECT_EQ(arm[3].loc.y, 0); 
    EXPECT_EQ(arm[3].loc.z, -2);

    EXPECT_EQ(arm[4].loc.x, 0);
    EXPECT_EQ(arm[4].loc.y, 2); 
    EXPECT_EQ(arm[4].loc.z, -2);
}

// Test rotate link 4 on the z axis by 15 clockwise
TEST(setRotation, case1)
{
    Link arm[5];
    arm[0] = Link(2, Vector(0,0,0), 359.0, 1.0, 100.0, Axis::y);
    arm[1] = Link(2, Vector(0,0,0), 359.0, 1.0, 100.0, Axis::y);
    arm[2] = Link(2, Vector(0,0,0), 359.0, 1.0, 100.0, Axis::y);
    arm[3] = Link(2, Vector(0,0,0), 359.0, 1.0, 100.0, Axis::y);
    arm[4] = Link(2, Vector(0,0,0), 359.0, 1.0, 100.0, Axis::y);

    forwardsKinematics(arm, 5);

    setRotation(arm, 4, 15, Axis::z);

    EXPECT_EQ(arm[4].rot.z, 15);
}

TEST(setRotation, case2)
{
    Link arm[5];
    arm[0] = Link(2, Vector(0,0,0), 359.0, 1.0, 100.0, Axis::y);
    arm[1] = Link(2, Vector(0,0,0), 359.0, 1.0, 100.0, Axis::y);
    arm[2] = Link(2, Vector(0,0,0), 359.0, 1.0, 100.0, Axis::y);
    arm[3] = Link(2, Vector(0,0,0), 359.0, 1.0, 100.0, Axis::y);
    arm[4] = Link(2, Vector(0,0,0), 359.0, 1.0, 100.0, Axis::y);

    forwardsKinematics(arm, 5);

    setRotation(arm, 3, 15, Axis::y);

    EXPECT_EQ(arm[3].rot.y, 15);
}

TEST(calculateRotation, case1){
    Vector v1(1.050644, 0 , 1.701807);
    Vector v2(2,0,0);

    v1.Normalize();
    v2.Normalize();

    double cosAngle = DotProduct(v1, v2);

    EXPECT_NEAR(58.5, calculateRotation(cosAngle), 0.3);
}