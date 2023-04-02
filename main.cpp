#include "tools/Color.h"
#include "tools/Point3D.h"
#include "tools/Vector3D.h"
#include "camera/Camera.h"
#include "scene/Sphere.h"
#include "scene/Plane.h"

#include <cstddef>
#include <utility>
#include <vector>
#include "iostream"
#include <cmath>

int main () {
    Plane plane1 = Plane(Point3D(2, 2, 2), Vector3D(0, 0, 1), Color(0, 0, 0), 0, 0, 0, 0, 0, 0);

    std::pair<Plane*, Point3D*> pair;

    pair = plane1.intercept(Point3D(0, 0, 0), Vector3D(1, 1, 1));

    if (pair.first == nullptr) {
        std::cout << "Doesnt intercept\n";
    }
    else {
        std::cout << "Intercepts\n";
    }

    Plane plane2 = Plane(Point3D(1, 0, 0), Vector3D(0, 0, 1), Color(0, 0, 0), 0, 0, 0, 0, 0, 0);

    pair = plane2.intercept(Point3D(0, 0, 0), Vector3D(1, 1, 1));

    if (pair.first == nullptr) {
        std::cout << "Doesnt intercept\n";
    }
    else {
        std::cout << "Intercepts\n";
    } 
}