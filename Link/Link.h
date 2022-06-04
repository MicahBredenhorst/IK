#include "Vector.h"

#ifndef LINK_H
#define LINK_H

class Link 
{
    public:
        Vector rot;     // Rotation of the link
        Vector loc;     // Location of the link
        double max_rz = 0;  // Maximum rotation
        double min_rz = 0;  // Mimimum rotation
        double damp_width = 0; 
        Link(){};

        Link(Vector rot, Vector loc){
            Link::rot = rot;
            Link::loc = loc;
        };

        Link(Vector rot, Vector loc, double max_rz, double min_rz, double damp_width){
            Link::rot = rot;
            Link::loc = loc;
            Link::max_rz = max_rz;
            Link::min_rz = min_rz;
            Link::damp_width = damp_width;
        };
};

#endif