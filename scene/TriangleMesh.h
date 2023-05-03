#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "../tools/Point3D.h"
#include "../tools/Color.h"
#include "../tools/Vector3D.h"

#include <iostream>
#include <vector>
#include <optional>
#include <cstddef>
#include <limits>
#include <tuple>
#include <cmath>

using namespace std;

class TriangleMesh {
public:
    vector<Point3D> vertices;
    vector<std::tuple<int, int, int>> triangleVertices;
    vector<Vector3D> triangleNormals;
    vector<Vector3D> vertexNormals;

    Color color = Color(0, 0, 0);
    float diffuseCoefficient;
    float specularCoefficient;
    float ambientCoefficient;
    float reflectionCoefficient;
    float transmissionCoefficient;
    float rugosityCoefficient;

    float bezierThreshold = 0.1;

    TriangleMesh();
    TriangleMesh(
        vector<Point3D> vertices,
        vector<std::tuple<int, int, int>> triangleVertices,
        Color color,
        float diffuseCoefficient, 
        float specularCoefficient,
        float ambientCoefficient,
        float reflectionCoefficient,
        float transmissionCoefficient,
        float rugosityCoefficient);
    // Used for bezier surfaces
    TriangleMesh(
        vector<vector<Point3D>> curves,
        Color color,
        float diffuseCoefficient, 
        float specularCoefficient,
        float ambientCoefficient,
        float reflectionCoefficient,
        float transmissionCoefficient,
        float rugosityCoefficient);
    
    std::optional<std::tuple<Vector3D, Point3D, TriangleMesh>> intercept(Point3D point, Vector3D vector);
    void calculateNormals();
};

#endif /* TRIANGLEMESH_H */