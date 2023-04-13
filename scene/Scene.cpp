#include "Scene.h"
#include "Triangle.h"
#include "TriangleMesh.h"

#include <algorithm>
#include <math.h>
#include <iostream>
#include <tuple>

Scene::Scene (Color color, std::vector<Sphere> spheres, std::vector<Plane> planes, std::vector<TriangleMesh> triangles, std::vector<Light> lights) {
    this->ambientColor = color;
    this->ambientColor.normalize();
    this->spheres = spheres;
    this->planes = planes;
    this->triangles = triangles;
    this->lights = lights;
}

Color Scene::intercept (Point3D point, Vector3D vector) {
    Color color = this->ambientColor;

    string interceptedObject = "";

    float interceptDistance = std::numeric_limits<float>::max();

    Point3D interceptedPoint;
    Triangle interceptedTriangle;
    Sphere interceptedSphere;
    Plane interceptedPlane;
    TriangleMesh interceptedTriangleMesh;

    for (auto sphere: this->spheres) {
        auto pair = sphere.intercept(point, vector);

        if (!pair) {
            continue;
        }
        else {
            float distance = point.distanceToPoint(pair.value().second);

            if (distance < interceptDistance) {
                interceptDistance = distance;
                interceptedObject = "sphere";

                interceptedPoint = pair.value().second;
                interceptedSphere = pair.value().first;
            }
        }
    }

    for (auto plane: this->planes) {
        auto pair = plane.intercept(point, vector);

        if (!pair) {
            continue;
        }
        else {
            float distance = point.distanceToPoint(pair.value().second);

            if (distance < interceptDistance) {
                interceptDistance = distance;
                interceptedObject = "plane";

                interceptedPoint = pair.value().second;
                interceptedPlane = pair.value().first;
            }
        }
    }

    for (auto triangleMesh: this->triangles) {
        auto result = triangleMesh.intercept(point, vector);

        if (!result) {
            continue;
        }
        else {
            float distance = point.distanceToPoint(std::get<1>(result.value()));

            if (distance < interceptDistance) {
                interceptDistance = distance;
                interceptedObject = "triangle";

                interceptedTriangle = std::get<0>(result.value());
                interceptedPoint = std::get<1>(result.value());
                interceptedTriangleMesh = std::get<2>(result.value());
            }
        }
    }

    if (interceptedObject == "") {
        // No interception
        color.denormalize();
        return color;
    }

    Vector3D V = interceptedPoint.getVectorToPoint(point);
    V.normalize();

    if (interceptedObject == "sphere") {
        color = phong(interceptedSphere.ambientCoefficient,
                        interceptedSphere.color, 
                        interceptedSphere.diffuseCoefficient, 
                        interceptedSphere.center.getVectorToPoint(interceptedPoint), 
                        interceptedSphere.specularCoefficient, 
                        V, 
                        interceptedSphere.rugosityCoefficient,
                        interceptedPoint);
    }
    else if (interceptedObject == "plane") {
        color = phong(interceptedPlane.ambientCoefficient,
                        interceptedPlane.color, 
                        interceptedPlane.diffuseCoefficient, 
                        interceptedPlane.normalVector, 
                        interceptedPlane.specularCoefficient, 
                        V, 
                        interceptedPlane.rugosityCoefficient,
                        interceptedPoint);
    }
    else if (interceptedObject == "triangle") {
        color = phong(interceptedTriangleMesh.ambientCoefficient,
                        interceptedTriangleMesh.color, 
                        interceptedTriangleMesh.diffuseCoefficient, 
                        interceptedTriangle.normal, 
                        interceptedTriangleMesh.specularCoefficient, 
                        V, 
                        interceptedTriangleMesh.rugosityCoefficient,
                        interceptedPoint);
    }

    return color;
}

Vector3D Scene::reflexionVector(Vector3D N, Vector3D L) {
    auto constant = N.dotProduct(L)*2; 
    N.multiply(constant);
    Vector3D auxVet;
    auxVet.setVector(N.x - L.x, N.y - L.y, N.z - L.z);
    return auxVet;
}

Color Scene::phong(float Ka, Color Od, float Kd, Vector3D N, float Ks, Vector3D V, float n, Point3D interceptionPoint){
    // Ambient component
    Color color = this->ambientColor;
    color.multiplyValue(Ka);

    for (auto light: this->lights) {
        // Diffuse component
        Color diffuse = Color(0, 0, 0);
        diffuse.sumColor(Od);

        diffuse.multiplyColor(light.color);

        diffuse.multiplyValue(Kd);

        Vector3D L = interceptionPoint.getVectorToPoint(light.localization);
        L.normalize();

        N.normalize();

        float zero = 0;

        diffuse.multiplyValue(std::max(zero, L.dotProduct(N)));

        color.sumColor(diffuse);

        // Specular component
        Color specular = light.color;

        specular.multiplyValue(Ks);

        Vector3D R  = this->reflexionVector(N, L);
        R.normalize();

        specular.multiplyValue(std::pow(R.dotProduct(V), n));

        color.sumColor(specular);
    }

    color.denormalize();

    return color;
}