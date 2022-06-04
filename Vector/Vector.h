#ifndef VECTOR_H
#define VECTOR_H

class Vector 
{
    public:
        double x;
        double y;
        double z;
        Vector(){}
        Vector(double x, double y, double z){
            Vector::x = x;
            Vector::y = y;
            Vector::z = z;
        };
        void Normalize();
        void Print();
        Vector Subtract(Vector v1);
};

#endif