#include "Point3D.h"
#include "Vector3D.h"

Point3D::Point3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point3D Point3D::sumVectorToPoint(Vector3D vector) {
    return Point3D(vector.x + this->x, vector.y + this->y, vector.z + this->z);
}

Vector3D Point3D::getVectorToPoint(Point3D point2) {
    return Vector3D(point2.x - this->x, point2.y - this->y, point2.z - this->z);
}