#ifndef MATRIX4x4_H
#define MATRIX4x4_H


#include <cmath>

class Matrix4X4 {
public:
    float matrix[4][4] = {{1.0f, 0.0f, 0.0f, 0.0f}, 
        {0.0f, 1.0f, 0.0f, 0.0f}, 
        {0.0f, 0.0f, 1.0f, 0.0f}, 
        {0.0f, 0.0f, 0.0f, 1.0f}};
    
    Matrix4X4();
    void toTranslationMatrix(float x, float y, float z); 
    void toRotationMatrix(double angle, char axis);
    void toClockwiseRotationMatrix(double angle, char axis);
};


#endif /* MATRIX4x4_H */