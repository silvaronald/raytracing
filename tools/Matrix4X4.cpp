#include "Matrix4X4.h"
#include <cmath>

Matrix4X4::Matrix4X4() {}

void Matrix4X4::toTranslationMatrix(float x, float y, float z) {
    this->matrix[0][3] = x;
    this->matrix[1][3] = y;
    this->matrix[2][3] = z;
}

void Matrix4X4::toRotationMatrix(double angle, char axis) {

    double radian = angle*M_PI/180.0;

    if(axis == 'X') {
        matrix[1][1] = (float) std::cos(radian);
        matrix[1][2] = (float) (-std::sin(radian));
        matrix[2][1] = (float) std::sin(radian);
        matrix[2][2] = (float) std::cos(radian);

    } else if(axis == 'Y'){
        matrix[0][0] = (float) std::cos(radian);
        matrix[0][2] = (float) std::sin(radian);
        matrix[2][0] = (float) (-std::sin(radian));
        matrix[2][2] = (float) std::cos(radian);

    } else if(axis == 'Z'){
        matrix[0][0] = (float) std::cos(radian);
        matrix[0][1] = (float) (-std::sin(radian));
        matrix[1][0] = (float) std::sin(radian);
        matrix[1][1] = (float) std::cos(radian);
    }

}

void Matrix4X4::toClockwiseRotationMatrix(double angle, char axis) {

    double radian = angle*M_PI/180.0;

    if(axis == 'X') {
        matrix[1][1] = (float) std::cos(radian);
        matrix[1][2] = (float) std::sin(radian);
        matrix[2][1] = (float) (-std::sin(radian));
        matrix[2][2] = (float) std::cos(radian);

    } else if(axis == 'Y'){
        matrix[0][0] = (float) std::cos(radian);
        matrix[0][2] = (float) (-std::sin(radian));
        matrix[2][0] = (float) std::sin(radian);
        matrix[2][2] = (float) std::cos(radian);

    } else if(axis == 'Z'){
        matrix[0][0] = (float) std::cos(radian);
        matrix[0][1] = (float) std::sin(radian);
        matrix[1][0] = (float) (-std::sin(radian));
        matrix[1][1] = (float) std::cos(radian);
    }

}

