#ifndef SCENE_H
#define SCENE_H

#include "../tools/Color.h"
#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"
#include "TriangleMesh.h"
#include "../camera/Camera.h"

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
    std::vector<TriangleMesh> trianglesMeshes;
    std::vector<Light> lights;
    int depth = 10;

    Camera camera;

    Vector3D reflexionVector(Vector3D N, Vector3D L);
    Vector3D refractionVector(Vector3D N, Vector3D L, float n);
    Color phong (float Ka, Color Od, float Kd, Vector3D N, float Ks, Vector3D V, float Kr, float Kt, float n, Point3D interceptionPoint, Point3D raycastPoint, int depth);
    Scene (Color color, std::vector<Sphere> spheres, std::vector<Plane> planes, std::vector<TriangleMesh> triangles, std::vector<Light> lights, Camera camera);
    Color intercept(Point3D point, Vector3D vector, int depth = 1);
};

#endif /* SCENE_H */
