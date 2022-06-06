#include "Vector.h"

#ifndef LINK_H
#define LINK_H

enum Rotation {clockwise, counterClockwise};
enum Axis {x, y, z};
class Link 
{
    public:
        Vector rot;     // Rotation of the link
        Vector loc;     // Location of the link
        double length;  // The lenght of the link
        double max_rz;  // Maximum rotation
        double min_rz;  // Mimimum rotation
        double damp_width;
        Axis axis;
        Link(){};

        Link(Vector loc, Vector rot) 
            : rot(rot), loc(loc)
        {}
        Link(double length, Vector rot)
            : length(length), rot(rot)
        {loc = Vector(0,0,0);}

        Link(double length, Vector rot, double max_rz, double min_rz, double damp_width, Axis axis)
            : length(length), rot(rot), max_rz(max_rz), min_rz(min_rz), damp_width(damp_width), axis(axis)
        {loc = Vector(0,0,0);}

        Link(Vector loc, Vector rot, double max_rz, double min_rz, double damp_width)
            : rot(rot), loc(loc), max_rz(max_rz), min_rz(min_rz), damp_width(damp_width)
        {}

        void Print();
};

#endif