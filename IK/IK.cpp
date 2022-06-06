#include "IK.h"
#include <iostream>
#include <math.h>
#include <cmath> 

#define FIRST_IN_LINK 0

// Damp the rotation based on the damp width
void dampRotation(double* turnDeg, Link* link)
{
    if(abs(*turnDeg) > link->damp_width)
    {
        if(*turnDeg > 0){
            *turnDeg = link->damp_width;
        }
        else{
            *turnDeg = -link->damp_width;
        }
    }
}

// Limit the rotation based on the domain of freedom
void restrictRotation(double* rot_axis, Link link)
{
    if(*rot_axis > 0.0 && *rot_axis > link.max_rz){
        *rot_axis = link.max_rz;
    }
    else if(*rot_axis < 0.0 && *rot_axis < link.min_rz){
        *rot_axis = link.min_rz;
    }
}

// Get the direction of the rotation
Rotation getRotationDirection(double crossProduct)
{
    if(crossProduct > 0.0)
        return Rotation::clockwise;
    else if(crossProduct < 0.0)
        return Rotation::counterClockwise;
}

// Calculate all the new vector locations after the rotation of a link.
// void applyRotation(Link *arm, Link* armPrevious, int size){
//     for(int i = 0; i < size - 1; i++){
//         //Apply the rotation on the z-axis.
//         // double rotation_z = arm[i].rot.z - armPrevious[i].rot.z;
        
//         Vector newLocation = arm[i].loc.RotateZAxis(arm[i].rot.z);
//         arm[i].loc = newLocation;

//         // Apply the rotation on the y-axis.
//         // double rotation_y = arm[i].rot.y - armPrevious[i].rot.y;

//         // Why should you resest it?

//         Vector newLocation2 = arm[i].loc.RotateYAxis(arm[i].rot.y);
//         arm[i].loc = newLocation2;
//         // Why is it not assigned?
//         arm[i].rot.Reset();   // Causes stack smash for some reason.
//     }
// }

double calculateRotation(double cosAngle){
    // direction is treived from crossResultAxis so maybe we need that.
    double turnAngle = acos((float)cosAngle);
    turnAngle = turnAngle * 180 / M_PI;
    return turnAngle;
}


void setRotation(Link arm[], int link, double turnAngle, Axis axis)
{
    dampRotation(&turnAngle, &arm[link]);    
    double* rotation_axis;
    switch(axis)
    {
        case x: rotation_axis = &arm[link].rot.x; break;
        case y: rotation_axis = &arm[link].rot.y; break;
        case z: rotation_axis = &arm[link].rot.z; break;
    }

    *rotation_axis += turnAngle;

    restrictRotation(rotation_axis, arm[link]);
}

void forwardsKinematics(Link arm[], int size)
{
    arm[FIRST_IN_LINK].loc = Vector(0,0,0); // Set root to root
    for(int i = 0; i < size - 1; i++)
    {  
        double currentAngleZ = 0;
        double currentAngleY = 0;

        for(int j = FIRST_IN_LINK; j <= i; j++){
            currentAngleZ = currentAngleZ + arm[j].rot.z;
            currentAngleY = currentAngleY + arm[j].rot.y;
        }

        if(i != FIRST_IN_LINK ){
            arm[i + 1].loc.x = arm[i].loc.x + arm[i].length * _cos(currentAngleY);
            arm[i + 1].loc.z = arm[i].loc.z + arm[i].length * _sin(currentAngleY);
            if(currentAngleZ != 0){
                arm[i + 1].loc.x = arm[i].loc.x + arm[i].length * _cos(currentAngleZ);
                arm[i + 1].loc.y = arm[i].loc.y + arm[i].length * _sin(currentAngleZ);
            }
        } 
        else{
            arm[i + 1].loc.x = arm[i].length * _cos(currentAngleY);
            arm[i + 1].loc.z = arm[i].length * _sin(currentAngleY);
            if(currentAngleZ != 0){
                arm[i + 1].loc.x = arm[i].length * _cos(currentAngleZ);
                arm[i + 1].loc.y = arm[i].length * _sin(currentAngleZ);
            }
        }
    }
}

double dTR(double degrees)
{   
    double temp = degrees / 180 * M_PI ;
}

double _sin(double degrees){
    if(std::abs(degrees) == 90 || std::abs(degrees) == 180){
        if(degrees == 90)
            return 1;
        else if(degrees == -90)
            return -1;
        else if(degrees == 180)
            return 0;
        else if(degrees == -180)
            return 0;
    }
    else{
        return sin(dTR(degrees));
    }
}

double _cos(double degrees){
    if(std::abs(degrees) == 90 || std::abs(degrees) == 180)
    {
        if(degrees == 90)
            return 0;
        else if(degrees == -90)
            return 0;
        else if(degrees == 180)
            return -1;
        else if(degrees == -180)
            return -1;
    }
    else{
        return cos(dTR(degrees));
    }
}
