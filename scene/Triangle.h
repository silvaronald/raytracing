#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"

class Triangle {
public:
    Point3D p1 = Point3D();
    Point3D p2 = Point3D();
    Point3D p3 = Point3D();
    Vector3D normal = Vector3D();

    Triangle(Point3D p1, Point3D p2, Point3D p3);
    void getNormal();
};

#endif /* TRIANGLE_H */