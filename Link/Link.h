#include "Vector.h"

#ifndef LINK_H
#define LINK_H

class Link 
{
    public:
        Vector rot;     // Rotation of the link
        Vector loc;     // Location of the link
        double max_rz;  // Maximum rotation
        double min_rz;  // Mimimum rotation
        double damp_width; 
        Link(){};

        Link(Vector loc, Vector rot) 
            : rot(rot), loc(loc)
        {}

        Link(Vector loc, Vector rot, double max_rz, double min_rz, double damp_width)
            : rot(rot), loc(loc), max_rz(max_rz), min_rz(min_rz), damp_width(damp_width)
        {}

        void Print();
};

#endif