#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D () {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3D::Vector3D (float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3D::setVector (float x, float y, float z) {
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

void Vector3D::normalize() {
    float norm = this->getNorm();

    this->x /= norm;
    this->y /= norm;
    this->z /= norm;
}

float Vector3D::getNorm() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

float Vector3D::dotProduct(Vector3D vector2) {
    return (this->x * vector2.x + this->y * vector2.y + this->z * vector2.z);
}

Vector3D Vector3D::projectOnto(Vector3D vector2) {
    Vector3D projection = vector2;
    projection.normalize();

    projection.multiply(this->dotProduct(vector2) / vector2.getNorm());

    return projection;
}

void Vector3D::print() {
    std::cout << "X: " << this->x << " / Y: " << this->y << " / Z: " << this->z << "\n";
}