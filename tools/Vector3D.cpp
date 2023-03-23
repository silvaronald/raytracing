#include "Vector3D.h"

Vector3D::Vector3D (float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3D::multiply(float factor) {
    this->x = this->x * factor;
    this->y = this->y * factor;
    this->z = this->z * factor;
}

Vector3D Vector3D::crossProduct(Vector3D vector2) {
    float x = (this->y * vector2.z) - (this->z * vector2.y);
    float y = (this->z * vector2.x) - (this->x * vector2.z);
    float z = (this->x * vector2.y) - (this->y * vector2.x);

    return Vector3D(x, y, z);
}