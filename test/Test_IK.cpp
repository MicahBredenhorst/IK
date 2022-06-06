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

// TEST(applyRotation, case1)
// {
//     // SEGEMENATION FAULT?
//     // Addition of rotation z part causes segmentation fault..
//     Link armPrevious[1];
//     armPrevious[0] = Link(Vector(5,3,1), Vector(0,0,0));

//     // This is a rotation on the y axis.
//     Link arm[1];
//     arm[0] = Link(Vector(5,3,1), Vector(0,-45,0));

//     applyRotation(arm, armPrevious);
//     EXPECT_NEAR(arm[0].loc.x, 2.828, 0.001);
//     EXPECT_NEAR(arm[0].loc.y, 3, 0.001);
//     EXPECT_NEAR(arm[0].loc.z, 4.243, 0.001);
// }

// TEST(applyRotation, case2)
// {
//     Link armPrevious[2];
//     armPrevious[0] = Link(Vector(5,3,1), Vector(0,0,0));

//     Link arm[2];
//     arm[0] = Link(Vector(5,3,1), Vector(0,-45,0));
    
// }

// TEST(applyRotation, case2)
// {
//     Link armPrevious[1];
//     armPrevious[0] = Link(Vector(5,3,1), Vector(0,10,0));

//     Link arm[1];
//     arm[0] = Link(Vector(5,3,1), Vector(0,10,0));

//     applyRotation(arm, armPrevious);
//     EXPECT_NEAR(arm[0].loc.x, 2.828, 0.001);
//     EXPECT_NEAR(arm[0].loc.y, 3, 0.001);
//     EXPECT_NEAR(arm[0].loc.z, 4.243, 0.001);
// }

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

