#include "Scene.h"

#include <algorithm>
#include <math.h>
#include <iostream>
#include <tuple>

Scene::Scene (Color color, std::vector<Sphere> spheres, std::vector<Plane> planes, std::vector<TriangleMesh> trianglesMeshes, std::vector<Light> lights, Camera camera) {
    this->ambientColor = color;
    this->spheres = spheres;
    this->planes = planes;
    this->trianglesMeshes = trianglesMeshes;
    this->lights = lights;
    this->camera = camera;
}

Color Scene::intercept (Point3D point, Vector3D vector, int depth) {
    Color color = this->ambientColor;

    string interceptedObject = "";

    float interceptDistance = std::numeric_limits<float>::max();

    Point3D interceptedPoint;
    Sphere interceptedSphere;
    Plane interceptedPlane;
    TriangleMesh interceptedTriangleMesh;
    Vector3D normalVector;

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

    for (int i = 0; i < this->trianglesMeshes.size(); i++) {
        auto result = this->trianglesMeshes[i].intercept(point, vector);

        if (!result) {
            continue;
        }
        else {
            float distance = point.distanceToPoint(std::get<1>(result.value()));

            if (distance < interceptDistance) {
                interceptDistance = distance;
                interceptedObject = "triangle";

                normalVector = std::get<0>(result.value());
                interceptedPoint = std::get<1>(result.value());
                interceptedTriangleMesh = std::get<2>(result.value());
            }
        }
    }

    for (auto triangleMesh: this->trianglesMeshes) {
        
        auto result = triangleMesh.intercept(point, vector);

        if (!result) {
            continue;
        }
        else {
            float distance = point.distanceToPoint(std::get<1>(result.value()));
            


            if (distance < interceptDistance) {
                interceptDistance = distance;
                interceptedObject = "triangle";

                normalVector = std::get<0>(result.value());
                interceptedPoint = std::get<1>(result.value());
                interceptedTriangleMesh = std::get<2>(result.value());
            }
        }
    }

    if (interceptedObject == "") {
        // No interception
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
                        interceptedSphere.reflectionCoefficient,
                        interceptedSphere.transmissionCoefficient,
                        interceptedSphere.rugosityCoefficient,
                        interceptedPoint,
                        point,
                        depth);
    }
    else if (interceptedObject == "plane") {
        if (interceptedPlane.normalVector.dotProduct(interceptedPlane.planePoint.getVectorToPoint(point)) < 0) {
            interceptedPlane.normalVector.multiply(-1);
        }

        color = phong(interceptedPlane.ambientCoefficient,
                        interceptedPlane.color, 
                        interceptedPlane.diffuseCoefficient, 
                        interceptedPlane.normalVector, 
                        interceptedPlane.specularCoefficient, 
                        V, 
                        interceptedPlane.reflectionCoefficient,
                        interceptedPlane.transmissionCoefficient,
                        interceptedPlane.rugosityCoefficient,
                        interceptedPoint,
                        point,
                        depth);
    }
    else if (interceptedObject == "triangle") {
        if (normalVector.dotProduct(interceptedPoint.getVectorToPoint(point)) < 0) {
            normalVector.multiply(-1);
        }

        color = phong(interceptedTriangleMesh.ambientCoefficient,
                        interceptedTriangleMesh.color, 
                        interceptedTriangleMesh.diffuseCoefficient, 
                        normalVector, 
                        interceptedTriangleMesh.specularCoefficient, 
                        V, 
                        interceptedTriangleMesh.reflectionCoefficient,
                        interceptedTriangleMesh.transmissionCoefficient,
                        interceptedTriangleMesh.rugosityCoefficient,
                        interceptedPoint,
                        point,
                        depth);
    }

    return color;
}

Vector3D Scene::reflexionVector(Vector3D N, Vector3D L) {
    auto constant = N.dotProduct(L)*2; 
    N.multiply(constant);
    Vector3D auxVet;
    auxVet.setVector(L.x - N.x, L.y - N.y, L.z - N.z);
    return auxVet;
}

Vector3D Scene::refractionVector(Vector3D incident, Vector3D normal, float eta) {
    Vector3D normal_inv = normal;
    normal_inv.multiply(-1.0f);
    float cos_i = normal.dotProduct(normal_inv);
    float sin_t2 = eta * sqrt(1.0f - cos_i * cos_i);
    if (sin_t2 >= 1.0f) {
        // Reflexão total interna
        return Vector3D(0, 0, 0);
    }
    float cos_t = sqrtf(1.0f - sin_t2 * sin_t2);
    Vector3D T;
    T.x = (eta * cos_i - cos_t) * normal.x + eta * incident.x;
    T.y = (eta * cos_i - cos_t) * normal.y + eta * incident.y;
    T.z = (eta * cos_i - cos_t) * normal.z + eta * incident.z;
    cout << "T: " << T.x << " " << T.y << " " << T.z << endl;
    return T;
}

Color Scene::phong(float Ka, Color Od, float Kd, Vector3D N, float Ks, Vector3D V, float Kr, float Kt, float n, Point3D interceptionPoint, Point3D raycastPoint, int depth){
    Color color = Color();

    // Ambient component
    if (depth == 1) {
        color.sumColor(this->ambientColor);
        color.multiplyValue(Ka);
    }

    Color DifSpec = Color(0,0,0);
    //kd ks ka kr kt p
    for (auto light: this->lights) {
        // Diffuse component
        Color diffuse = Color(0, 0, 0);
        diffuse.sumColor(Od);

        diffuse.multiplyColor(light.color);

        diffuse.multiplyValue(Kd);

        Vector3D L = interceptionPoint.getVectorToPoint(light.localization);
        L.normalize();

        N.normalize();

        diffuse.multiplyValue(std::max(0.f, L.dotProduct(N)));
        
        color.sumColor(diffuse);

        // Specular component
        Color specular = light.color;

        specular.multiplyValue(Ks);

        Vector3D R  = this->reflexionVector(N, L);
        R.normalize();

        specular.multiplyValue(std::pow(std::max(0.f,R.dotProduct(V)), n));

        color.sumColor(specular);
    }

    // Recursive call
    if (depth < this->depth - 1) {
        // Reflexion
        if (Kr > 0) {
            Vector3D R = this->reflexionVector(N, interceptionPoint.getVectorToPoint(raycastPoint));
            R.normalize();

            Color reflexion = this->intercept(interceptionPoint, R, depth + 1);
            reflexion.multiplyValue(Kr);

            color.sumColor(reflexion);
        }

        // Refraction  
        if(Kt > 0) {
            Vector3D T = this->refractionVector(V, N, Kt);

            if (!(T.x == 0 && T.y == 0 && T.z == 0)) { // checking for total reflexion
                T.normalize();

                Color refraction = this->intercept(interceptionPoint, T, depth + 1);
                refraction.multiplyValue(Kt);

                color.sumColor(refraction);
            }
        }
    }

    return color;
}