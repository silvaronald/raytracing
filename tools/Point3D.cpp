#include "Point3D.h"
#include "Vector3D.h"
#include <cmath>

Point3D::Point3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point3D::Point3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point3D Point3D::setCoordinates(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
}

Point3D Point3D::sumVectorToPoint(Vector3D vector) {
    return Point3D(this->x + vector.x, this->y + vector.y, this->z + vector.z);
}

Vector3D Point3D::getVectorToPoint(Point3D point2) {
    return Vector3D(point2.x - this->x, point2.y - this->y, point2.z - this->z);
}

float Point3D::distanceToPoint(Point3D point2) {
    return sqrt(pow(this->x - point2.x, 2) + pow(this->y - point2.y, 2) + pow(this->z - point2.z, 2));
}

void Point3D::print() {
    std::cout << "X: " << this->x << " / Y: " << this->y << " / Z: " << this->z << "\n";
}