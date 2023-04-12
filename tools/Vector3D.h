#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
class Vector3D {
public:
    float x;
    float y;
    float z;
    Vector3D ();
    Vector3D (float x, float y, float z);
    void setVector (float x, float y, float z);
    void multiply (float factor);
    Vector3D crossProduct (Vector3D vector2);
    void normalize ();
    float getNorm ();
    float dotProduct (Vector3D vector2);
    Vector3D projectOnto (Vector3D vector2);
    void print ();
};

#endif /* VECTOR3D_H */
