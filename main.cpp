#include "scene/Light.h"
#include "tools/Color.h"
#include "tools/Point3D.h"
#include "tools/Vector3D.h"
#include "camera/Camera.h"
#include "scene/Sphere.h"
#include "scene/Plane.h"
#include "scene/TriangleMesh.h"
#include "scene/Triangle.h"
#include "scene/Scene.h"

#include <cstddef>
#include <utility>
#include <vector>
#include "iostream"
#include <cmath>

int main () {
    vector<Point3D> vertices;
    vector<vector<int>> triangleIdxs;

    vertices.push_back(Point3D(1,1,1));
    vertices.push_back(Point3D(1,1,0));
    vertices.push_back(Point3D(1,0,0));
    vertices.push_back(Point3D(1,0,1));
    vertices.push_back(Point3D(0,0,1));
    vertices.push_back(Point3D(0,0,0));
    vertices.push_back(Point3D(0,1,0));
    vertices.push_back(Point3D(0,1,1));

    triangleIdxs = {{0,3,1}, {1,3,2}, {2,3,5}, {3,4,5}, {4,7,5}, {5,7,6}};

    TriangleMesh malha = TriangleMesh(6, 8, vertices, triangleIdxs, Color(255, 0, 0), 1, 1, 1, 0, 0, 5);

    malha.rotate(30.0, 'X');
}