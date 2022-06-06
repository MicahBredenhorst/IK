// Inverse kinematics using CCD

#include <iostream>
#include "Vector.h"
#include "Math.h"
#include <math.h>
#include "Link.h"
#include "IK.h"

#include <algorithm>
#include <iterator>

#define EFFECTOR_POS 5     // Amount of links in chain
#define MAX_IK_TRIES 20
#define IK_POS_THRES 0.8f

Link arm[EFFECTOR_POS];
Vector rootPos, curEnd, desiredEnd, targetVector, curVector, crossResult, endPos;

double cosAngle, turnAngle, turnDeg;
bool isDampingEnabled = false;
bool isDOFEnabled = false;

int link = EFFECTOR_POS - 2; 
int tries = 0;

void PrintArm()
{
    for(int i = 0; i < EFFECTOR_POS; i++)
    {
        arm[i].loc.Print();
    }
}

int main(){
    // Create links for the arm
    arm[0] = Link(2, Vector(0,0,0), 359.0, 1.0, 1.0, Axis::y);
    arm[1] = Link(2, Vector(0,0,0), 359.0, 1.0, 1.0, Axis::z);
    arm[2] = Link(2, Vector(0,0,0), 359.0, 1.0, 1.0, Axis::z);
    arm[3] = Link(2, Vector(0,0,0), 359.0, 1.0, 1.0, Axis::z);

    // Example 1:
    //desiredEnd = Vector(0, 3, 0); 

    // Example 2:
    desiredEnd = Vector(0, 2, -2);

    forwardsKinematics(arm, EFFECTOR_POS);    // Calculate all vectors

    do
    { 
        // FIXME: There is a moment where the root and end are the same?
        rootPos = arm[link].loc;
        curEnd = arm[EFFECTOR_POS - 1].loc;

        std::cout << "Current End effector: " << std::endl;
        curEnd.Print();
        std::cout << "Current rootPos: " << std::endl;
        rootPos.Print(); 

        std::cout << "VSD: " << VectorSquaredDistance(curEnd, desiredEnd) << std::endl;
        if(VectorSquaredDistance(curEnd, desiredEnd) > IK_POS_THRES)
        {
            // Calculate the rotation for a specific link.
            curVector = curEnd.Subtract(rootPos); 
            targetVector = desiredEnd.Subtract(rootPos);

            curVector.Normalize();
            targetVector.Normalize();

            double cosAngle = DotProduct(curVector, targetVector);
            std::cout << cosAngle << std::endl;

            // Set the correct rotation axis
            Axis axis = arm[link].axis;

            if(cosAngle < 0.99999){
                double crossResultAxis;
                switch(axis){
                    case x: crossResultAxis = CrossProduct(targetVector, curVector).x; break;
                    case y: crossResultAxis = CrossProduct(targetVector, curVector).y; break;
                    case z: crossResultAxis = CrossProduct(targetVector, curVector).z; break;
                }
                if(crossResultAxis != 0.0){
                    Rotation direction = getRotationDirection(crossResultAxis);
                    double turnAngle = calculateRotation(cosAngle);
                    if(direction == Rotation::counterClockwise)
                        turnAngle = -turnAngle;
                    setRotation(arm, link, turnAngle, axis);
                }
            }
            // Calculate the rotation of the entire chain.
            std::cout << "Try: " << tries << std::endl;              
            forwardsKinematics(arm, EFFECTOR_POS);
            PrintArm();  
            if(--link < 0){
                link = EFFECTOR_POS - 2; // Restart
            } 
        }

        if(VectorSquaredDistance(curEnd, desiredEnd) < IK_POS_THRES)
        {
            std::cout << "VSD: " << VectorSquaredDistance(curEnd, desiredEnd) << std::endl;
            std::cout << "End effector in range of threshold" << std::endl;
            break;
        }
    }
    while(tries++ < MAX_IK_TRIES);
    std::cout << "END" << std::endl;
    PrintArm();
    return true;
}