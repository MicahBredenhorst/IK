// Inverse kinematics using CCD

#include <iostream>
#include "Vector.h"
#include "Math.h"
#include <math.h>
#include "Link.h"
#include "IK.h"

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

// FIXME this needs global values which makes it difficult to test
// Set the rotation object of a link to the correct rotation.
void setRotation(double cosAngle, Axis axis, Rotation direction)
{
    double turnAngle = acos((float)cosAngle);
    turnDeg = RadiansToDegree(turnAngle);
    if(isDampingEnabled)
        dampRotation(&turnDeg, &arm[link]);

    double* rotation_axis;
    switch(axis)
    {
        case x: rotation_axis = &arm[link].rot.x; break;
        case y: rotation_axis = &arm[link].rot.y; break;
        case z: rotation_axis = &arm[link].rot.z; break;
    }

    if(direction == Rotation::clockwise){
        *rotation_axis -= turnDeg;
    }
    else{
        *rotation_axis += turnDeg;
    }

    if(isDOFEnabled)
        restrictRotation(rotation_axis, arm[link], direction);
}

int main(){
    
    // Create links for the arm
    arm[0] = Link(Vector(0,0,0), Vector(0,0,0));
    arm[1] = Link(Vector(1,0,0), Vector(0,0,0));
    arm[2] = Link(Vector(2,0,0), Vector(0,0,0));
    
    // FIXME: what goes wrong here?
    endPos = Vector(1.8,0,0); 

    for(int i = 0; i < EFFECTOR_POS; i++){
        std::cout << "Attempt: " << tries << std::endl;
        arm[tries].Print();
    }
    do
    {     
        std::copy(std::begin(arm), std::end(arm), std::begin(armPrevious));

        // These are changed, do I have to do this more o
        rootPos = arm[link].loc;
        curEnd = arm[EFFECTOR_POS].loc;
        desiredEnd = endPos;

        if(VectorSquaredDistance(curEnd, desiredEnd) > IK_POS_THRES)
        {
            // Calculate the rotation for a specific link.
            curVector = curEnd.Subtract(rootPos); 
            targetVector = endPos.Subtract(rootPos);

            curVector.Normalize();
            targetVector.Normalize();

            double cosAngle = DotProduct(curVector, targetVector);
            
            // In the other doc we provided the axis however we have to do it for all right?
            Axis axis = z;
            // Set the rotation on a specific link.
            if(cosAngle > 0.99999){
                double crossResultAxis;
                switch(axis){
                    case x: crossResultAxis = CrossProduct(targetVector, curVector).x; break;
                    case y: crossResultAxis = CrossProduct(targetVector, curVector).y; break;
                    case z: crossResultAxis = CrossProduct(targetVector, curVector).z; break;
                }
                if(crossResultAxis != 0.0){
                    Rotation direction = getRotationDirection(crossResultAxis);
                    setRotation(cosAngle, axis, direction);
                }
            }
            // Calculate the rotation of the entire chain.
            // TODO: rethink the order of this item.
            applyRotation(arm, armPrevious);

            if(--link < 0) link = EFFECTOR_POS - 1; // Restart
        }
    }
    while(tries++ < MAX_IK_TRIES && VectorSquaredDistance(curEnd, desiredEnd) > IK_POS_THRES);
    return true;
}