#include "Plane.h"
#include <cstddef>
#include <utility>
#include <iostream>
#include <optional>
#include "../tools/Matrix4X4.h"
#include "../tools/MatrixOperations.h"

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

    this->diffuseCoefficient = diffuseCoefficient;
    this->specularCoefficient = specularCoefficient;
    this->ambientCoefficient = ambientCoefficient;
    this->reflectionCoefficient = reflectionCoefficient;
    this->transmissionCoefficient = transmissionCoefficient;
    this->rugosityCoefficient = rugosityCoefficient;
}

void Plane::translade(float x, float y, float z) {
    Matrix4X4 translationMatrix;
    translationMatrix.toTranslationMatrix(x,y,z);

    this->planePoint = pointMatrixMultiplication(this->planePoint.x,this->planePoint.y, this->planePoint.z, translationMatrix);
}

void Plane::rotate(double angle, char axis) {
    Matrix4X4 rotationMatrix;
    rotationMatrix.toRotationMatrix(angle, axis);

    this->normalVector = vectorMatrixMultiplication(this->normalVector.x, this->normalVector.y, this->normalVector.z, rotationMatrix);
}

std::optional<std::pair<Plane, Point3D>> Plane::intercept(Point3D point, Vector3D vector) {
    std::optional<std::pair<Plane, Point3D>> pair;

    Vector3D vectorCameraToPlane = Vector3D(this->planePoint.x - point.x, this->planePoint.y - point.y, this->planePoint.z - point.z);

    Vector3D projectionVector = vectorCameraToPlane.projectOnto(vector);

    if (projectionVector.x / vector.x <= 1 || projectionVector.y / vector.y <= 1 || projectionVector.z / vector.z <= 1) {
        // is at most behind the screen
        return std::nullopt;
    }
    
    Point3D projectionPoint = point.sumVectorToPoint(projectionVector);

    Vector3D vectorPlaneToProjection = Vector3D(this->planePoint.x - projectionPoint.x, this->planePoint.y - projectionPoint.y, this->planePoint.z - projectionPoint.z);

    if (vectorPlaneToProjection.dotProduct(normalVector) == 0) {
        // intercepts
        pair = std::make_pair(*this, projectionPoint);

        return pair;
    }

    return std::nullopt;
}