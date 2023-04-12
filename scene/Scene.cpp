#include "Scene.h"
#include "Triangle.h"
#include <math.h>
#include <iostream>

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

    this->interceptedPoint = interceptedPoint;

    Vector3D N, V; 
    if (interceptedObject == "sphere") {
        color = interceptedSphere.color;
        N = interceptedSphere.center.getVectorToPoint(interceptedPoint);
    }
    else if (interceptedObject == "plane") {
        color = interceptedPlane.color;
        N = interceptedPlane.normalVector;
    }
    else if (interceptedObject == "triangle") {
        //color = interceptedTriangle.color;
        color = Color(-1, -1, -1);
        N = interceptedTriangle.normal; 
    }

    V = interceptedPoint.getVectorToPoint(point);

    color = this->phong(0.2, this->ambientColor, lights.size(), color, 0.2, N, 0.5, V, 1);

    return color;
}

Vector3D Scene::lightVector(Point3D point, Light lights) {
    return point.getVectorToPoint(lights.localization);
}

Vector3D Scene::reflexionVector(Vector3D N, Vector3D L) {

    auto constant = N.dotProduct(L)*2; 
    N.multiply(constant);
    Vector3D auxVet;
    auxVet.setVector(N.x - L.x, N.y - L.y, N.z - L.z);
    return auxVet;

}

Color Scene::phong(float Ka, Color Ia, int m, Color Od, float Kd, Vector3D N, float Ks, Vector3D V, float n){
    Color color = Color(0, 0, 0);
    Ia.multiplyValue(Ka);
    color.sumColor(Ia);
    for (auto light: this->lights) {
        Vector3D L = this->lightVector(interceptedPoint, light);
        cout << "Os dados do vetor L são: "<< L.x << L.y << L.z << "\n" << "Os dados dos pontos sao "  << interceptedPoint.x << interceptedPoint.y << interceptedPoint.z<< endl;
        cout << "Os dados da luz sao: " << light.localization.x << light.localization.y << light.localization.z << "\n";
        Vector3D R  = this->reflexionVector(N, L);
        auto Ili = light.color;
        light.color.multiplyValue(Kd);
        light.color.multiplyColor(Od);


        
        float cosTheta = N.dotProduct(L);
        if (cosTheta < 0) {
            cosTheta = 0;
        }


        float cosPhi = R.dotProduct(V);

        if (cosPhi < 0) {
            cosPhi = 0;
        }

        light.color.multiplyValue(cosTheta);
        auto L1 = light.color;

        Ili.multiplyValue(Ks);
        Ili.multiplyValue(pow(cosPhi, n));

        color.sumColor(L1);
        color.sumColor(Ili);
    }

    return color;
}