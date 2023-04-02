#include "Plane.h"
#include <cstddef>
#include <utility>
#include <iostream>

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

    this->diffuseCoefficient = diffuseCoefficient;
    this->specularCoefficient = specularCoefficient;
    this->ambientCoefficient = ambientCoefficient;
    this->reflectionCoefficient = reflectionCoefficient;
    this->transmissionCoefficient = transmissionCoefficient;
    this->rugosityCoefficient = rugosityCoefficient;
}

std::pair<Plane*, Point3D*> Plane::intercept(Point3D point, Vector3D vector) {
    Vector3D vectorCameraToPlane = Vector3D(this->planePoint.x - point.x, this->planePoint.y - point.y, this->planePoint.z - point.z);

    Vector3D projectionVector = vectorCameraToPlane.projectOnto(vector);

    if ((projectionVector.x / vector.x) <= 1) {
        // is at most behind the screen
        return std::make_pair(nullptr, nullptr);
    }
    
    Point3D projectionPoint = point.sumVectorToPoint(projectionVector);

    Vector3D vectorPlaneToProjection = Vector3D(this->planePoint.x - projectionPoint.x, this->planePoint.y - projectionPoint.y, this->planePoint.z - projectionPoint.z);

    std::cout << vectorPlaneToProjection.dotProduct(normalVector) << '\n';

    if (vectorPlaneToProjection.dotProduct(normalVector) == 0) {
        // intercepts
        return std::make_pair(this, new Point3D(projectionPoint));
    }
    else {
        return std::make_pair(nullptr, nullptr);
    }
}