#include "tools/Color.h"
#include "tools/Point3D.h"
#include "tools/Vector3D.h"
#include "camera/Camera.h"
#include "scene/Sphere.h"
#include "scene/TriangleMesh.h"
#include "scene/Triangle.h"

#include <vector>
#include "iostream"
#include <cmath>

int main () {
    Triangle tri1 = Triangle(Point3D(-7.52087,5.78212,0), Point3D(-5.02851,6.25767,0), Point3D(5,3,2));
    Triangle tri2 = Triangle(Point3D(4,3,1), Point3D(-5.02851,6.25767,0), Point3D(5,3,2));
    vector<Triangle> triangles = {tri1, tri2};
    vector<Point3D> points;
    vector<Vector3D> normals;
    vector<Vector3D> vNormals;
    TriangleMesh tMesh = TriangleMesh(2, 4, points, triangles, normals, vNormals, Color(0, 0, 0), 0, 0, 0, 0, 0, 0);

    auto interception = tMesh.intercept(Point3D(0, 0, 0), Vector3D(0, 0, 1));

    if (!interception) {
        cout << "Doesn't intercept\n";
    }
    else {
        std::cout << interception.value().second.x << " " << interception.value().second.y << " " << interception.value().second.z << "\n";
    }
}