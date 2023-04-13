#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "../tools/Point3D.h"
#include "../tools/Color.h"
#include "Triangle.h"

#include <vector>
#include <optional>
#include <cstddef>
#include <limits>
#include <tuple>

using namespace std;

class TriangleMesh {
public:
    int numTriangles;
    int numVertices;
    vector<Point3D> vertices;
    vector<Triangle> triangles;
    vector<Vector3D> triangleNormals;
    vector<Vector3D> vertexNormals;
    Color color = Color(0, 0, 0);

    float diffuseCoefficient;
    float specularCoefficient;
    float ambientCoefficient;
    float reflectionCoefficient;
    float transmissionCoefficient;
    float rugosityCoefficient;

    TriangleMesh();
    TriangleMesh(
        int numTriangles, 
        int numVertices, 
        vector<Point3D> vertices,
        vector<Triangle> triangles,
        vector<Vector3D> triangleNormals,
        vector<Vector3D> vertexNormals, 
        Color color,
        float diffuseCoefficient, 
        float specularCoefficient,
        float ambientCoefficient,
        float reflectionCoefficient,
        float transmissionCoefficient,
        float rugosityCoefficient);
    
    std::optional<std::tuple<Triangle, Point3D, TriangleMesh>> intercept(Point3D point, Vector3D vector);
};

#endif /* TRIANGLEMESH_H */