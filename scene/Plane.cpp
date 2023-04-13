#include "Plane.h"
#include <cstddef>
#include <utility>
#include <iostream>
#include <optional>

Plane::Plane() {}

Plane::Plane(
    Point3D planePoint, 
    Vector3D normalVector, 
    Color color, 
    float diffuseCoefficient, 
    float specularCoefficient,
    float ambientCoefficient,
    float reflectionCoefficient,
    float transmissionCoefficient,
    float rugosityCoefficient) {

    this->planePoint = planePoint;
    this->normalVector = normalVector;
    this->color = color;
    this->color.normalize();

    this->diffuseCoefficient = diffuseCoefficient;
    this->specularCoefficient = specularCoefficient;
    this->ambientCoefficient = ambientCoefficient;
    this->reflectionCoefficient = reflectionCoefficient;
    this->transmissionCoefficient = transmissionCoefficient;
    this->rugosityCoefficient = rugosityCoefficient;
}

std::optional<std::pair<Plane, Point3D>> Plane::intercept(Point3D point, Vector3D vector) {
    std::optional<std::pair<Plane, Point3D>> pair;

    Vector3D vectorCameraToPlane = point.getVectorToPoint(this->planePoint);

    float denominator = vector.dotProduct(this->normalVector);

    if (denominator == 0) {
        // line is parallel to plane
        return std::nullopt;
    }

    float numerator = vectorCameraToPlane.dotProduct(this->normalVector);

    float t = numerator / denominator;

    if (t <= 1) {
        // is at most behind the screen
        return std::nullopt;
    }
    
    vector.multiply(t);

    Point3D intersectionPoint = point.sumVectorToPoint(vector);

    pair = std::make_pair(*this, intersectionPoint);

    return pair;
}