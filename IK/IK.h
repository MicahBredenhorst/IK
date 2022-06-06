#include "Link.h"

enum Axis {x, y, z};
enum Rotation {clockwise, counterClockwise};
void dampRotation(double* turnDeg, Link* link);
void restrictRotation(double* rot_axis, Link link, Rotation direction);
Rotation getRotationDirection(double crossProduct);
void applyRotation(Link *arm, Link *armPrevious);
void forwardsKinematics(Link arm[], int size);
double _sin(double degrees);
double _cos(double degrees);
double dTR(double degrees);