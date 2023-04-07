#include "Scene.h"
#include "Triangle.h"

Scene::Scene (Color color, std::vector<Sphere> spheres, std::vector<Plane> planes, std::vector<TriangleMesh> triangles, std::vector<Light> lights) {
    this->ambientColor = color;
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
        auto pair = triangleMesh.intercept(point, vector);

        if (!pair) {
            continue;
        }
        else {
            float distance = point.distanceToPoint(pair.value().second);

            if (distance < interceptDistance) {
                interceptDistance = distance;
                interceptedObject = "triangle";

                interceptedPoint = pair.value().second;
                interceptedTriangle = pair.value().first;
            }
        }
    }

    if (interceptedObject == "sphere") {
        color = interceptedSphere.color;
    }
    else if (interceptedObject == "plane") {
        color = interceptedPlane.color;
    }
    else if (interceptedObject == "triangle") {
        //color = interceptedTriangle.color;
        color = Color(-1, -1, -1);
    }

    return color;
}