#include "Camera.h"
#include "../tools/Matrix4X4.h"
#include "../tools/MatrixOperations.h"

Camera::Camera (int screenWidth, int screenHeight, float distanceToScreen, Vector3D vectorUp, Point3D localization, Point3D target) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->distanceToScreen = distanceToScreen;
    this->vectorUp = vectorUp;
    this->localization = localization;
    this->target = target;

    this->updateCamera();
}

void Camera::updateCamera() {
    this->vectorTarget = Vector3D(this->target.x - this->localization.x, this->target.y - this->localization.y, this->target.z - this->localization.z);

    this->vectorW = this->vectorTarget;
    this->vectorW.multiply(-1);
    this->vectorW.normalize();

    this->vectorX = this->vectorW.crossProduct(this->vectorUp);
    this->vectorX.normalize();

    this->vectorY = this->vectorW.crossProduct(this->vectorX);
    this->vectorY.normalize();
}

void Camera::translade(float x, float y, float z) {
    Matrix4X4 translationMatrix;
    translationMatrix.toTranslationMatrix(x,y,z);

    this->localization = pointMatrixMultiplication(this->localization.x, this->localization.y, this->localization.z, translationMatrix);

    this->updateCamera();
}

void Camera::rotate(double angle, char axis) {
    Matrix4X4 transladeCenter, rotate, transladeBack;

    transladeCenter.toTranslationMatrix(-this->localization.x, -this->localization.y, -this->localization.z);
    rotate.toRotationMatrix(angle, axis);
    transladeBack.toTranslationMatrix(this->localization.x, this->localization.y, this->localization.z);

    this->vectorUp = vectorMatrixMultiplication(this->vectorUp.x, this->vectorUp.y, this->vectorUp.z, rotate);

    this->target = pointMatrixMultiplication(this->target.x, this->target.y, this->target.z, transladeCenter);
    this->target = pointMatrixMultiplication(this->target.x, this->target.y, this->target.z, rotate);
    this->target = pointMatrixMultiplication(this->target.x, this->target.y, this->target.z, transladeBack);

    this->updateCamera();
}