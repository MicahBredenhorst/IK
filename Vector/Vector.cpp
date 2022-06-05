#include "Vector.h"
#include <iostream>

//#include "Math.h" // this is a problem

#include <math.h>

void Vector::Print()
{
    std::cout.precision(8);
    std::cout << "X:" << x << " Y:" << y << " Z:" << z << std::endl;
}

void Vector::Normalize()
{
    double magnitude = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)); 
    this->x = this->x / magnitude;
    this->y = this->y / magnitude;
    this->z = this->z / magnitude;
}

Vector Vector::Subtract(Vector v1)
{
    Vector vOut;
    vOut.x = this->x - v1.x;
    vOut.y = this->y - v1.y;
    vOut.z = this->z - v1.z;
    return vOut;
}

Vector Vector::RotateZAxis(double angle)
{
    // A rotation on the z axis causes movement on the x and y axis.
    Vector vOut;
    double radians = angle * M_PI / 180;
    vOut.x = cos(radians) * this->x - sin(radians) * this->y;
    vOut.y = sin(radians) * this->x + cos(radians) * this->y;
    return vOut;
}

Vector Vector::RotateYAxis(double angle)
{
    // A rotation on the y axis causes movement on x and z axis
    Vector vOut;
    double radians = angle * M_PI / 180;
    vOut.x = sin(radians) * this->z + cos(radians) * this->x;
    vOut.z = cos(radians) * this->z - sin(radians) * this->x;
    return vOut;
}