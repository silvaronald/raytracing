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
#include <fstream>

int SCREEN_WIDTH = 90;
int SCREEN_HEIGHT = 160;

int main () {
    Camera camera = Camera(SCREEN_WIDTH, SCREEN_HEIGHT, 5, Vector3D(1, 0, 0), Point3D(0, 0, -5), Point3D(0, 0, 0));

    vector<Sphere> spheres;

    spheres.push_back(Sphere(Point3D(0, 0, 10000), 7500, Color(0, 0, 200), 0, 0, 0, 0, 0, 0));

    vector<Plane> planes;

    planes.push_back(Plane(Point3D(0, 0, 20000), Vector3D(0, 0, -1), Color(100, 1, 0), 0, 0, 0, 0, 0, 0));

    vector<Light> lights;

    vector<TriangleMesh> triangles;

    Scene scene = Scene(Color(255, 255, 255), spheres, planes, triangles, lights);

    // Raycasting
    ofstream outfile("output.ppm", ios::out | ios::binary);

    int max_value = 255;

    outfile << "P6\n" << SCREEN_WIDTH << " " << SCREEN_HEIGHT << "\n" << max_value << "\n";

    // Iterate through screen
    // Height is even
    if (SCREEN_HEIGHT % 2 == 0) {
        for (float i = (SCREEN_HEIGHT / 2.0) - 1 + 0.5; i > -(SCREEN_HEIGHT / 2.0); i--) {
            Vector3D verticalVector = camera.vectorY;
            verticalVector.multiply(i);

            // Width is even
            if (SCREEN_WIDTH % 2 == 0) {
                for (float j = -(SCREEN_WIDTH / 2.0) + 0.5; j < SCREEN_WIDTH / 2.0; j++) {
                    Vector3D horizontalVector = camera.vectorX;
                    horizontalVector.multiply(j);

                    Point3D screenPoint = camera.target.sumVectorToPoint(verticalVector);

                    screenPoint = screenPoint.sumVectorToPoint(horizontalVector);
                    
                    Vector3D cameraToScreen = camera.localization.getVectorToPoint(screenPoint);

                    Color color = scene.intercept(camera.localization, cameraToScreen);

                    outfile << (char)color.red << (char)color.green << (char)color.blue;
                }
            }
            // Width is odd
            else {
                for (float j = ceil(-(SCREEN_WIDTH / 2.0)); j < SCREEN_WIDTH / 2.0; j++) {
                    Vector3D horizontalVector = camera.vectorX;
                    horizontalVector.multiply(j);

                    Point3D screenPoint = camera.target.sumVectorToPoint(verticalVector);

                    screenPoint = screenPoint.sumVectorToPoint(horizontalVector);
                    
                    Vector3D cameraToScreen = camera.localization.getVectorToPoint(screenPoint);

                    Color color = scene.intercept(camera.localization, cameraToScreen);

                    outfile << (char)color.red << (char)color.green << (char)color.blue;
                }
            }
        }
    }
    // Height is odd
    else {
        for (float i = std::ceil(SCREEN_HEIGHT / 2.0); i > -SCREEN_HEIGHT / 2.0; i--) {
            Vector3D verticalVector = camera.vectorY;
            verticalVector.multiply(i);

            // Width is even
            if (SCREEN_WIDTH % 2 == 0) {
                for (float j = -(SCREEN_WIDTH / 2.0) + 0.5; j < SCREEN_WIDTH / 2.0; j++) {
                    Vector3D horizontalVector = camera.vectorX;
                    horizontalVector.multiply(j);

                    Point3D screenPoint = camera.target.sumVectorToPoint(verticalVector);

                    screenPoint = screenPoint.sumVectorToPoint(horizontalVector);
                    
                    Vector3D cameraToScreen = camera.localization.getVectorToPoint(screenPoint);

                    Color color = scene.intercept(camera.localization, cameraToScreen);

                    outfile << (char)color.red << (char)color.green << (char)color.blue;
                }
            }
            // Width is odd
            else {
                for (float j = ceil(-(SCREEN_WIDTH / 2.0)); j < SCREEN_WIDTH / 2.0; j++) {
                    Vector3D horizontalVector = camera.vectorX;
                    horizontalVector.multiply(j);

                    Point3D screenPoint = camera.target.sumVectorToPoint(verticalVector);

                    screenPoint = screenPoint.sumVectorToPoint(horizontalVector);
                    
                    Vector3D cameraToScreen = camera.localization.getVectorToPoint(screenPoint);

                    Color color = scene.intercept(camera.localization, cameraToScreen);

                    outfile << (char)color.red << (char)color.green << (char)color.blue;
                }
            }
        }
    }
    outfile.close();

    return 0;
}