#include "tools/Color.h"
#include "tools/Point3D.h"
#include "tools/Vector3D.h"

#include "iostream"

int main () {
    Point3D point(1, -1, 2);
    Point3D point1(5, 3, -2.5);

    Vector3D vector(2, 2, 0);

    //std::cout << point.x << " " << point.y << " " << point.z << "\n";

    point = point.sumVectorToPoint(vector);

    //std::cout << point.x << " " << point.y << " " << point.z << "\n";

    Vector3D vector1 = point.getVectorToPoint(point1);

    std::cout << vector1.x << " " << vector1.y << " " << vector1.z << "\n";

    Vector3D vecCross = vector.crossProduct(vector1);

    std::cout << vecCross.x << " " << vecCross.y << " " << vecCross.z << "\n";
}