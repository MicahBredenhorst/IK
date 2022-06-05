// Inverse kinematics using CCD

#include <iostream>
#include "Vector.h"
#include "Math.h"
#include <math.h>
#include "Link.h"

#include <algorithm>
#include <iterator>

#define EFFECTOR_POS 3     // Amount of links in chain
#define MAX_IK_TRIES 4
#define IK_POS_THRES 1.0f
#define ENABLEDDAMPING false
#define ENABLEDOF false

Link armPrevious[EFFECTOR_POS];
Link arm[EFFECTOR_POS];
Vector rootPos, curEnd, desiredEnd, targetVector, curVector, crossResult, endPos;

double cosAngle, turnAngle, turnDeg;
bool isDampingEnabled = false;
bool isDOFEnabled = false;

int link = EFFECTOR_POS - 1; 
int tries = 0;

enum Axis {x, y, z};
enum Rotation {clockwise, counterClockwise};
//
// ISSUES:
// Those pointer functions are not working correctly
// The enum is not working correctly
//




void dampTurn(double *turnDeg){
    if(isDampingEnabled && *turnDeg > arm[link].damp_width)
    {
        arm[link].damp_width;
    }
}

void setRotation(double* rot_axis, Link arm_link, bool rotateLeft)
{
    if (rotateLeft) {
        *rot_axis += turnDeg;
        // DOF restriction
        if(isDOFEnabled && *rot_axis > arm_link.max_rz)
        {
            *rot_axis = arm_link.max_rz;
        }
    }
    else {
        *rot_axis -= turnDeg;
        // DOF restriction
        if(isDOFEnabled && *rot_axis < arm_link.min_rz)
        {
            *rot_axis = arm_link.min_rz;
        }
    }    
}

void turnLink(double cosineAngle, bool rotateLeft, Axis axis){
    turnAngle = acos((float)cosAngle);
    turnDeg = RadiansToDegree(turnAngle);
    dampTurn(&turnDeg);

    double* rotation_axis;
    switch(axis)
    {
        case x: rotation_axis = &arm[link].rot.x; break;
        case y: rotation_axis = &arm[link].rot.y; break;
        case z: rotation_axis = &arm[link].rot.z; break;
    }

    if (rotateLeft) {

        setRotation(rotation_axis, arm[link], true);
    }
    else {
        setRotation(rotation_axis, arm[link], false);
    }    
}

int main(){
    
    // Create links for the arm
    arm[0] = Link(Vector(0,0,0), Vector(0,0,0));
    arm[1] = Link(Vector(1,0,0), Vector(0,0,0));
    arm[2] = Link(Vector(2,0,0), Vector(0,0,0));
    
    // FIXME: what goes wrong here?

    endPos = Vector(1.8,0,0); 

    do
    {     
        std::copy(std::begin(arm), std::end(arm), std::begin(armPrevious));

        // These are changed, do I have to do this more o
        rootPos = arm[link].loc;
        curEnd = arm[EFFECTOR_POS].loc;
        desiredEnd = endPos;

        // FIXME: Tries is already zero?

        // Print arm:
        for(int i = 0; i < EFFECTOR_POS; i++){
            std::cout << "Attempt: " << tries << std::endl;
            arm[tries].Print();
        }

        // FIXME: some need to be cloned instead of copied due to unintended changes that are being made


        if(VectorSquaredDistance(curEnd, desiredEnd) > IK_POS_THRES)
        {

            // VSD is in 3D and we only need to check it once before rotating in two directions


            curVector = curEnd.Subtract(rootPos);             // Create the vector to the current effector position
            targetVector = endPos.Subtract(rootPos);          // Create the desired effector position vector

            // Normalize the vectors
            curVector.Normalize();
            targetVector.Normalize();

            // Calculate the dotproduct giving the cosine of the desired angle
            cosAngle = DotProduct(targetVector, curVector);

            if(cosAngle < 0.99999)
            {
                crossResult = CrossProduct(targetVector, curVector);
                if(crossResult.z > 0.0)    // Rotate Clockwise on z-axis
                {
                    Axis axis = z;
                    turnLink(cosAngle, false, axis);
                }
                else if(crossResult.z < 0.0)  // Rotate Counter Clockwise on z-axis
                {
                    Axis axis = z;
                    turnLink(cosAngle, true, axis);
                }

                if(crossResult.y > 0.0)
                {
                    // Rotate Clockwise on y-axis
                    // RESEARCH: Can I reuse this angle or not?
                    Axis axis = y;
                    turnLink(cosAngle, true, axis);
                }
                else if(crossResult.y < 0.0)
                {
                    // Rotate counter clockwise on the y-axis
                    Axis axis = y;
                    turnLink(cosAngle, false, axis);
                }     
            }

            if(--link < 0) link = EFFECTOR_POS - 1; // Restart
            // Of you change the link here then the calculations will wrong?
        }
        // HERE IS THE PLACE WHERE THE RECALC TAKES PLACE.


        for(int i = 0; i < EFFECTOR_POS; i++){
            // It first moves everything based on the z turn direction
            // Get rotation change in the z direction
            double rotation_z = arm[i].rot.z - armPrevious[i].rot.z; // is the direction correct? 
            Vector newLocation = arm[i].loc.RotateZAxis(rotation_z);
            arm[i].loc = newLocation;

            // Then it should move everything based on the y turn direction
            double rotation_y = arm[i].rot.y - armPrevious[i].rot.y;
            Vector newLocation2 = arm[i].loc.RotateYAxis(rotation_y);
            arm[i].loc = newLocation2;
        }
    }
    while(tries++ < MAX_IK_TRIES && VectorSquaredDistance(curEnd, desiredEnd) > IK_POS_THRES);
    return true;
}