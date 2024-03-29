#ifndef POINT3D_H
#define POINT3D_H

#include "Vector3D.h"

class Point3D {
public:
    float x;
    float y;
    float z;

    Point3D ();
    Point3D (float x, float y, float z);

    Point3D sumVectorToPoint (Vector3D vector);
    Point3D multiply (float factor);
    Vector3D getVectorToPoint (Point3D point2);
    float distanceToPoint (Point3D point2);
    void sumPoint (Point3D point2);
};

#endif /* POINT3D_H */
