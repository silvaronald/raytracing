#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "../tools/Point3D.h"
#include "../tools/Color.h"
#include "Triangle.h"
#include <vector>
using namespace std;

class TriangleMesh {
public:
    int numTriangles;
    int numVertices;
    vector<Point3D> vertices;
    vector<Triangle> triangles; //TODO
    vector<Vector3D> triangleNormals;
    vector<Vector3D> vertexNormals;
    Color color = Color(0, 0, 0);

    TriangleMesh(
        int numTriangles, 
        int numVertices, 
        vector<Point3D> vertices,
        vector<Triangle> triangles, //TODO
        vector<Vector3D> triangleNormals,
        vector<Vector3D> vertexNormals, 
        Color color);
};

#endif /* TRIANGLEMESH_H */