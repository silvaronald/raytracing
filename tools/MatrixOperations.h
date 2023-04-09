#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

#include "Matrix4X4.h"
#include "Point3D.h"
#include "Vector3D.h"

Matrix4X4 matrixMultiplication(Matrix4X4 matrix1, Matrix4X4 matrix2) {
    Matrix4X4 result;

    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            result.matrix[i][j] = matrix1.matrix[i][0]*matrix2.matrix[0][j] + matrix1.matrix[i][1]*matrix2.matrix[1][j] + matrix1.matrix[i][2]*matrix2.matrix[2][j] + matrix1.matrix[i][3]*matrix2.matrix[3][j];
        }
    }
    return result;
}

Point3D pointMatrixMultiplication(float x, float y, float z, Matrix4X4 matrix){
    Point3D result;

    result.x = matrix.matrix[0][0]*x + matrix.matrix[0][1]*y + matrix.matrix[0][2]*z + matrix.matrix[0][3];
    result.y = matrix.matrix[1][0]*x + matrix.matrix[1][1]*y + matrix.matrix[1][2]*z + matrix.matrix[1][3];
    result.z = matrix.matrix[2][0]*x + matrix.matrix[2][1]*y + matrix.matrix[2][2]*z + matrix.matrix[2][3];

    return result;
}

Vector3D vectorMatrixMultiplication(float x, float y, float z, Matrix4X4 matrix){
    Vector3D result;

    result.x = matrix.matrix[0][0]*x + matrix.matrix[0][1]*y + matrix.matrix[0][2]*z + matrix.matrix[0][3];
    result.y = matrix.matrix[1][0]*x + matrix.matrix[1][1]*y + matrix.matrix[1][2]*z + matrix.matrix[1][3];
    result.z = matrix.matrix[2][0]*x + matrix.matrix[2][1]*y + matrix.matrix[2][2]*z + matrix.matrix[2][3];

    return result;
}


#endif