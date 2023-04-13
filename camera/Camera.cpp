#include "Camera.h"

Camera::Camera() {};

Camera::Camera (int screenWidth, int screenHeight, float distanceToScreen, Vector3D vectorUp, Point3D localization, Point3D target) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->distanceToScreen = distanceToScreen;
    this->vectorUp = vectorUp;
    this->localization = localization;
    this->target = target;

    this->vectorTarget = Vector3D(target.x - localization.x, target.y - localization.y, target.z - localization.z);

    this->vectorW = vectorTarget;
    this->vectorW.normalize();

    this->vectorX = this->vectorW.crossProduct(this->vectorUp);
    this->vectorX.normalize();

    this->vectorY = this->vectorX.crossProduct(this->vectorW);
    this->vectorY.normalize();
}