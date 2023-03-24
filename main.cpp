#include "tools/Color.h"
#include "tools/Point3D.h"
#include "tools/Vector3D.h"
#include "camera/Camera.h"

#include "iostream"

int main () {
    Camera camera(50, 50, 150, Vector3D(1,1,1), Point3D(0, 0, 5), Point3D(0, 0, 0));

    std::cout << camera.vectorW.x << " " << camera.vectorW.y << " " << camera.vectorW.z << "\n";
    std::cout << camera.vectorX.x << " " << camera.vectorX.y << " " << camera.vectorX.z << "\n";
    std::cout << camera.vectorY.x << " " << camera.vectorY.y << " " << camera.vectorY.z << "\n";
}