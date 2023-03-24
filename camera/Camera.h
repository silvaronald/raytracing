#ifndef CAMERA_H
#define CAMERA_H

#include "../tools/Vector3D.h"
#include "../tools/Point3D.h"

class Camera {
public:
    Point3D localization = Point3D(0,0,0);
    Point3D target = Point3D(0,0,0);

    int screenWidth;
    int screenHeight;

    float distanceToScreen;

    Vector3D vectorTarget = Vector3D(0,0,0);

    Vector3D vectorUp = Vector3D(0,0,0);

    Vector3D vectorW = Vector3D(0,0,0);
    Vector3D vectorX = Vector3D(0,0,0);
    Vector3D vectorY = Vector3D(0,0,0);

    Camera (int screenWidth, int screenHeight, float distanceToScreen, Vector3D vectorUp, Point3D localization, Point3D target);
};

#endif /* CAMERA_H */
