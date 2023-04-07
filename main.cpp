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
    vector<Sphere> spheres;
    spheres.push_back(Sphere(Point3D(0, 0, 10), 2, Color(200, 200, 200), 0, 0, 0, 0, 0, 0));

    vector<Plane> planes;
    planes.push_back(Plane(Point3D(0, 0, 20), Vector3D(0, 0, -1), Color(100, 100, 100), 0, 0, 0, 0, 0, 0));

    vector<Light> lights;

    vector<TriangleMesh> triangles;

    Scene scene = Scene(Color(1, 1, 1), spheres, planes, triangles, lights);

    Color color1 = scene.intercept(Point3D(0, 0, 0), Vector3D(0, 0, 11.9));

    std::cout << color1.red << " " << color1.green << " " << color1.blue << "\n";
}