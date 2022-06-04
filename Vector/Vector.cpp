#include "Vector.h"
#include <iostream>
#include <math.h>

void Vector::Print()
{
    std::cout.precision(8);
    std::cout << "X: " << x << std::endl;
    std::cout << "Y: " << y << std::endl;
    std::cout << "Z: " << z << std::endl;
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