#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D {
public:
    float x;
    float y;
    float z;

    Vector3D (float x, float y, float z);
    void multiply (float factor);
    Vector3D crossProduct (Vector3D vector2);
};

#endif /* VECTOR3D_H */
