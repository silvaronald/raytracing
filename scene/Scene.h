#ifndef SCENE_H
#define SCENE_H

#include "../tools/Color.h"
#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"
#include "TriangleMesh.h"

#include <vector>
#include <string>
#include <limits>
#include <utility>
#include <algorithm>

class Scene {
public:
    Color ambientColor = Color(0, 0, 0);

    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
    std::vector<TriangleMesh> triangles;
    std::vector<Light> lights;
    Point3D interceptedPoint;

    
    Vector3D lightVector(Point3D point, Light lights);
    Vector3D reflexionVector(Vector3D N, Vector3D L);
    Color phong(float Ka, Color Ia, int m, Color Od, float Kd, Vector3D N, float Ks, Vector3D V, float n);
    Scene (Color color, std::vector<Sphere> spheres, std::vector<Plane> planes, std::vector<TriangleMesh> triangles, std::vector<Light> lights);
    Color intercept(Point3D point, Vector3D);
};

#endif /* SCENE_H */
