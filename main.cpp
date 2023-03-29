#include "tools/Color.h"
#include "tools/Point3D.h"
#include "tools/Vector3D.h"
#include "camera/Camera.h"
#include "scene/Sphere.h"

#include <vector>
#include "iostream"
#include <cmath>

int main () {
    Sphere sphere = Sphere(Point3D(-5.47, 8.33, -3.09), sqrt(1.58), Color(0, 0, 0), 0, 0, 0, 0, 0, 0);

    std::cout << sphere.intercept(Point3D(0, 0, 0), Vector3D(-0.62, 0.95, -0.35)) << "\n";
    std::cout << sphere.intercept(Point3D(0, 0, 5), Vector3D(-1.77, 2.7, 1)) << "\n";
}