#include <iostream>
#include "Vector.h"
#include "Math.h"
#include <math.h>
#include "Link.h"

#define EFFECTOR_POS 3     // Amount of links in chain
#define MAX_IK_TRIES 100
#define IK_POS_THRES 1.0f
#define ENABLEDDAMPING false
#define ENABLEDOF false

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
    arm[0] = Link(Vector(0,0,0), Vector(0,0,0));
    arm[1] = Link(Vector(0,0,0), Vector(0,0,0));
    arm[2] = Link(Vector(0,0,0), Vector(0,0,0));
    endPos = Vector(0,0,0); 


    do
    {        
        rootPos = arm[link].loc;
        curEnd = arm[EFFECTOR_POS].loc;
        desiredEnd = endPos;

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
                    // turnAngle = acos((float)cosAngle);
                    // turnDeg = RadiansToDegree(turnAngle);

                    // // Damping
                    // if(isDampingEnabled && turnDeg > arm[link].damp_width)
                    // {
                    //     turnDeg = arm[link].damp_width;
                    // }

                    // arm[link].rot.z -= turnDeg;

                    // // DOF restriction

                    // if(isDOFEnabled && arm[link].rot.z < arm[link].min_rz)
                    // {
                    //     arm[link].rot.z = arm[link].min_rz;
                    // }
                }
                else if(crossResult.z < 0.0)  // Rotate Counter Clockwise
                {
                    turnLink(cosAngle, true);
                    // turnAngle = acos((float)cosAngle);
                    // turnDeg = RadiansToDegree(turnAngle);
                    
                    // // Damping
                    // if(isDampingEnabled && turnDeg > arm[link].damp_width)
                    // {
                    //     turnDeg = arm[link].damp_width;
                    // }
                    
                    // arm[link].rot.z += turnDeg;

                    // // DOF restriction
                    // if(isDOFEnabled && arm[link].rot.z > arm[link].max_rz)
                    // {
                    //     arm[link].rot.z = arm[link].max_rz;
                    // }

                }
            }
            if(--link < 0) link = EFFECTOR_POS - 1; // Restart
        }
    }
    while(tries++ < MAX_IK_TRIES && VectorSquaredDistance(curEnd, desiredEnd) > IK_POS_THRES);
    std::cout << "Blub" << std::endl;
    return true;
}