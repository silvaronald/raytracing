#ifndef PLANE_H
#define PLANE_H

#include "../tools/Color.h"
#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"
#include <utility>
#include <optional>

class Plane {
public:
    Point3D planePoint = Point3D(0, 0, 0);
    Vector3D normalVector = Vector3D(0, 0, 0);
    Color color = Color(0, 0, 0);

    float diffuseCoefficient;
    float specularCoefficient;
    float ambientCoefficient;
    float reflectionCoefficient;
    float transmissionCoefficient;
    float rugosityCoefficient;

    Plane (Point3D planePoint, 
        Vector3D normalVector, 
        Color color, 
        float diffuseCoefficient, 
        float specularCoefficient,
        float ambientCoefficient,
        float reflectionCoefficient,
        float transmissionCoefficient,
        float rugosityCoefficient);

    std::optional<std::pair<Plane, Point3D>> intercept(Point3D point, Vector3D vector);
};

#endif /* PLANE_H */
