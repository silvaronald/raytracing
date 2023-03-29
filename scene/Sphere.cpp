#include "Sphere.h"

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

    this->diffuseCoefficient = diffuseCoefficient;
    this->specularCoefficient = specularCoefficient;
    this->ambientCoefficient = ambientCoefficient;
    this->reflectionCoefficient = reflectionCoefficient;
    this->transmissionCoefficient = transmissionCoefficient;
    this->rugosityCoefficient = rugosityCoefficient;
}

float Sphere::intercept(Point3D point, Vector3D vector) {
    Vector3D assistVector = Vector3D (this->center.x - point.x, this->center.y - point.y, this->center.z - point.z);

    Vector3D projectionVector = assistVector.projectOnto(vector);

    Point3D projectionPoint = point.sumVectorToPoint(projectionVector);

    if (projectionPoint.distanceToPoint(this->center) <= radius) {
        // intercepts
        return 0;
    }
    
    else {
        return -1;
    }
}