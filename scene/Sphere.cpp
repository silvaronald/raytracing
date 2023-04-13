#include "Sphere.h"

#include <algorithm>
#include <cmath>
#include "iostream"
#include <optional>
#include <utility>

Sphere::Sphere() {}

Sphere::Sphere(Point3D center, 
        float radius, 
        Color color, 
        float diffuseCoefficient, 
        float specularCoefficient,
        float ambientCoefficient,
        float reflectionCoefficient,
        float transmissionCoefficient,
        float rugosityCoefficient) {
    
    this->center = center;
    this->radius = radius;
    this->color = color;
    this->color.normalize();

    this->diffuseCoefficient = diffuseCoefficient;
    this->specularCoefficient = specularCoefficient;
    this->ambientCoefficient = ambientCoefficient;
    this->reflectionCoefficient = reflectionCoefficient;
    this->transmissionCoefficient = transmissionCoefficient;
    this->rugosityCoefficient = rugosityCoefficient;
}

std::optional<std::pair<Sphere, Point3D>> Sphere::intercept(Point3D point, Vector3D vector) {
    std::optional<std::pair<Sphere, Point3D>> pair;

    // check implementation on notion page
    float a = vector.dotProduct(vector);

    Vector3D centerToPoint = Vector3D(point.x - this->center.x, point.y - this->center.y, point.z - this->center.z);

    float b = 2 * vector.dotProduct(centerToPoint);

    float c = centerToPoint.dotProduct(centerToPoint) - pow(radius, 2);

    float delta = pow(b, 2) - (4 * a * c);

    if (delta < 0) {
        return std::nullopt;
    }

    float t1 = (-b - sqrt(delta)) / (2 * a);

    float t2 = (-b + sqrt(delta)) / (2 * a);

    float t;

    if (t1 <= 1 && t2 <= 1) {
        return std::nullopt;
    }

    else if (t1 <= 1 && t2 > 1) {
        t = t2;
    }

    else if (t2 <= 1 && t1 > 1) {
        t = t1;
    }

    else if (t1 > 1 && t2 > 1) {
        t = std::min(t1, t2);
    }

    vector.multiply(t);

    pair = std::make_pair(*this, point.sumVectorToPoint(vector));

    return pair;
}