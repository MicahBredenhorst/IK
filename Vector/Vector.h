#ifndef VECTOR_H
#define VECTOR_H

class Vector 
{
    public:
        double x;
        double y;
        double z;
        Vector(){}
        Vector(double x, double y, double z)
            :x(x), y(y), z(z)
        {}
        void Normalize();
        void Print();
        void Reset();
        Vector Subtract(Vector v1);
        Vector RotateZAxis(double angle);
        Vector RotateYAxis(double angle);
};

#endif