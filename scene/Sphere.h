#ifndef SPHERE_H
#define SPHERE_H

#include "../tools/Point3D.h"
#include "../tools/Color.h"


#include <optional>
#include <utility>

class Sphere {
public:
    Point3D center = Point3D(0, 0, 0);
    float radius;
    Color color = Color(0, 0, 0);

    float diffuseCoefficient;
    float specularCoefficient;
    float ambientCoefficient;
    float reflectionCoefficient;
    float transmissionCoefficient;
    float rugosityCoefficient;

    Sphere ();
    Sphere (Point3D center, 
        float radius, 
        Color color, 
        float diffuseCoefficient, 
        float specularCoefficient,
        float ambientCoefficient,
        float reflectionCoefficient,
        float transmissionCoefficient,
        float rugosityCoefficient);

    void translade(float x, float y, float z);

    std::optional<std::pair<Sphere, Point3D>> intercept (Point3D point, Vector3D vector);
};

#endif /* SPHERE_H */
SPHERE_H