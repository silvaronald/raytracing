#include "Triangle.h"
#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"
#include <cmath>

Triangle::Triangle() {}

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

std::optional<Point3D> Triangle::intercept(Point3D point, Vector3D vector) {
    // Step 1: Check if the line intersects the plane of the triangle
    float denom = this->normal.dotProduct(vector);

    if (fabs(denom) == 0) {  // Parallel or coincident
        return std::nullopt;  // No intersection
    }

    float t = -(this->normal.dotProduct(this->p1.getVectorToPoint(point))) / denom;

    if (t <= 1) {
        // Point is behind screen
        return std::nullopt;
    }

    vector.multiply(t);

    Point3D intersectionPoint = point.sumVectorToPoint(vector);

    // Step 2: Check if the intersection point is inside the triangle
    Vector3D v0 = this->p1.getVectorToPoint(this->p2);
    Vector3D v1 = this->p1.getVectorToPoint(this->p3);
    Vector3D v2 = this->p1.getVectorToPoint(intersectionPoint);

    float d00 = v0.dotProduct(v0);
    float d01 = v0.dotProduct(v1);
    float d11 = v1.dotProduct(v1);
    float d20 = v2.dotProduct(v0);
    float d21 = v2.dotProduct(v1);

    float denom2 = d00 * d11 - d01 * d01;

    float alpha = (d11 * d20 - d01 * d21) / denom2;
    float beta = (d00 * d21 - d01 * d20) / denom2;

    if (alpha >= 0 && beta >= 0 && (alpha + beta) <= 1) {
        std::optional<Point3D> point = std::nullopt;
        point = intersectionPoint;
        return point;  // Intersection found
    }
    else {
        return std::nullopt;  // No intersection
    }
}