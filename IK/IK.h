#include "Link.h"

void dampRotation(double* turnDeg, Link* link);
void restrictRotation(double* rot_axis, Link link);
void setRotation(Link arm[], int link, double turnAngle, Axis axis);
Rotation getRotationDirection(double crossProduct);
void applyRotation(Link *arm, Link *armPrevious, int size);
void forwardsKinematics(Link arm[], int size);
double _sin(double degrees);
double _cos(double degrees);
double dTR(double degrees);
double calculateRotation(double cosAngle);