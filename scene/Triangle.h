#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"

#include <optional>

class Triangle {
public:
    Point3D p1 = Point3D();
    Point3D p2 = Point3D();
    Point3D p3 = Point3D();
    Vector3D normal = Vector3D();

    Triangle();
    Triangle(Point3D p1, Point3D p2, Point3D p3);
    void getNormal();
    
    std::optional<Point3D> intercept(Point3D point, Vector3D vector);
};

#endif /* TRIANGLE_H */