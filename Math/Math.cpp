#include "Math.h"
#include <math.h>
#include <Vector.h>


double DotProduct(Vector v1, Vector v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double RadiansToDegree(double radians)
{
    return (radians * 180 / M_PI);
}

double VectorSquaredDistance(Vector v1, Vector v2)
{
    return pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2);
}