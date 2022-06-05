#include "IK.h"



// Damp the rotation based on the damp width
void dampRotation(double* turnDeg, Link* link)
{
    if(*turnDeg > link->damp_width)
    {
        *turnDeg = link->damp_width;
    }
}

// Limit the rotation based on the domain of freedom
void restrictRotation(double* rot_axis, Link link, Rotation direction)
{
    if(direction == Rotation::clockwise && *rot_axis > link.max_rz){
        *rot_axis = link.max_rz;
    }
    else if(direction == Rotation::counterClockwise && *rot_axis < link.min_rz){
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
void applyRotation(Link *arm, Link *armPrevious){
    for(int i = 0; i < (sizeof(arm)/sizeof(*arm)); i++){
        // Apply the rotation on the z-axis.
        double rotation_z = arm[i].rot.z - armPrevious[i].rot.z;
        Vector newLocation = arm[i].loc.RotateZAxis(rotation_z);
        arm[i].loc = newLocation;

        // Apply the rotation on the y-axis.
        double rotation_y = arm[i].rot.y - armPrevious[i].rot.y;
        Vector newLocation2 = arm[i].loc.RotateYAxis(rotation_y);
        arm[i].loc = newLocation2;
    }
}
