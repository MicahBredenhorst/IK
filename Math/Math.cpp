#include "Math.h"
#include <math.h>
#include "Vector.h"


double DotProduct(Vector v1, Vector v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double RadiansToDegree(double radians)
{
    return (radians * 180 / M_PI);
}

double DegreesToRadians(double degrees)
{
    return degrees * M_PI / 180;
}

double VectorSquaredDistance(Vector v1, Vector v2)
{
    return pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2);
}

Vector CrossProduct(Vector v1, Vector v2)
{
    Vector vOut;
    vOut.x = v1.y * v2.z - v1.z * v2.y;
    vOut.y = v1.z * v2.x - v1.x * v2.z;
    vOut.z = v1.x * v2.y - v1.y * v2.x;
    return vOut;
}