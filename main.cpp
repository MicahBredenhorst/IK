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




void dampTurn(double* turnDeg){
    if(isDampingEnabled && *turnDeg > arm[link].damp_width)
    {
        arm[link].damp_width;
    }
}

void turnLink(double cosineAngle, bool rotateLeft){
    turnAngle = acos((float)cosAngle);
    turnDeg = RadiansToDegree(turnAngle);

    dampTurn(&turnDeg);

    if (rotateLeft) {
        arm[link].rot.z += turnDeg;

        // DOF restriction
        if(isDOFEnabled && arm[link].rot.z > arm[link].max_rz)
        {
            arm[link].rot.z = arm[link].max_rz;
        }
    }
    else {
        arm[link].rot.z -= turnDeg;

        // DOF restriction
        if(isDOFEnabled && arm[link].rot.z < arm[link].min_rz)
        {
            arm[link].rot.z = arm[link].min_rz;
        }
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
        rootPos = arm[link].loc;
        curEnd = arm[EFFECTOR_POS].loc;
        desiredEnd = endPos;

        // FIXME: Tries is already zero?

        // Print arm:
        for(int i = 0; i < EFFECTOR_POS; i++){
            std::cout << "Attempt: " << tries << std::endl;
            arm[tries].Print();
        }

        if(VectorSquaredDistance(curEnd, desiredEnd) > IK_POS_THRES)
        {
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
                if(crossResult.z > 0.0)    // Rotate Clockwise
                {
                    turnLink(cosAngle, false);
                }
                else if(crossResult.z < 0.0)  // Rotate Counter Clockwise
                {
                    turnLink(cosAngle, true);
                }
            }
            if(--link < 0) link = EFFECTOR_POS - 1; // Restart
        }
        // HERE IS THE PLACE WHERE THE RECALC TAKES PLACE.
        for(int i = 0; i < EFFECTOR_POS; i++){
            // Get rotation change in the z direction
            double rotation = arm[i].rot.z - armPrevious[i].rot.z; // is the direction correct? 
            Vector newLocation = arm[i].loc.Rotate(rotation);
            arm[i].loc = newLocation;
        }

    }
    while(tries++ < MAX_IK_TRIES && VectorSquaredDistance(curEnd, desiredEnd) > IK_POS_THRES);
    return true;
}