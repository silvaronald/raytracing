#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "../tools/Point3D.h"
#include "../tools/Color.h"
#include "../tools/Matrix4X4.h"
#include "../tools/MatrixOperations.h"
#include "Triangle.h"
#include <vector>
#include <optional>

using namespace std;

class TriangleMesh {
public:
    int numTriangles;
    int numVertices;
    vector<Point3D> vertices;
    vector<vector<int>> trianglesIdxs;
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
        vector<vector<int>> trianglesIdxs, 
        Color color,
        float diffuseCoefficient, 
        float specularCoefficient,
        float ambientCoefficient,
        float reflectionCoefficient,
        float transmissionCoefficient,
        float rugosityCoefficient);
    
    void updateMesh();
    std::optional<std::pair<vector<Vector3D>, vector<Vector3D>>> getNormals(vector<Triangle> triangles, vector<Point3D> vertices);

    std::optional<std::pair<Triangle, Point3D>> intercept(Point3D point, Vector3D vector);

    void translade(float x, float y, float z);
    void rotate(double angle, char axis);

    Point3D getMeshCenter();
};



#endif /* TRIANGLEMESH_H */