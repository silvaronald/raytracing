#include "Triangle.h"
#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"

Triangle::Triangle(Point3D p1, Point3D p2, Point3D p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    getNormal();
}

void Triangle::getNormal()
{
    Vector3D v1 = p1.getVectorToPoint(p2);
    Vector3D v2 = p1.getVectorToPoint(p3);
    this->normal = v1.crossProduct(v2);
    this->normal.normalize();
};