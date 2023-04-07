#include "Triangle.h"
#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"
#include <cmath>

Triangle::Triangle(Point3D p1, Point3D p2, Point3D p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    getNormal();
}

void Triangle::getNormal()
{
    Vector3D v1 = p1.getVectorToPoint(p2);
    Vector3D v2 = p1.getVectorToPoint(p3);
    this->normal = v1.crossProduct(v2);
    this->normal.normalize();
};

/*A FIM DE TESTE DE IMPLEMENTAÇÃO DOS TRIANGULOS*/
Point3D Triangle::interceptToPlane(Point3D point, Vector3D vector) {
    // TODO
    float a = this->normal.x;
    float b = this->normal.y;
    float c = this->normal.z;
    float d = -(a * this->p1.x + b * this->p1.y + c * this->p1.z);
    float t = -(a * point.x + b * point.y + c * point.z + d) / (a * vector.x + b * vector.y + c * vector.z);
    return (Point3D(point.x + t * vector.x, point.y + t * vector.y, point.z + t * vector.z));
}

bool Triangle::isInsideTriangle(Point3D point) {
    float alpha, beta, gamma;
    // A = p1, B = p2, C = p3
    Vector3D v0 = p2.getVectorToPoint(p1);
    Vector3D v1 = p3.getVectorToPoint(p1);
    Vector3D v2 = point.getVectorToPoint(p1);
    float d00 = v0.dotProduct(v0);
    float d01 = v0.dotProduct(v1);
    float d11 = v1.dotProduct(v1);
    float d20 = v2.dotProduct(v0);
    float d21 = v2.dotProduct(v1);
    float denom = d00 * d11 - d01 * d01;
    beta = (d11 * d20 - d01 * d21) / denom;
    gamma = (d00 * d21 - d01 * d20) / denom;
    alpha = 1.0f - beta - gamma;
    
    // Verificação se a soma das coordenadas baricêntricas é igual a 1
    return ((alpha + beta + gamma) == 1);
}
