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

class Scene {
public:
    Color ambientColor = Color(0, 0, 0);

    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
    std::vector<TriangleMesh> triangles;
    std::vector<Light> lights;

    Scene (Color color, std::vector<Sphere> spheres, std::vector<Plane> planes, std::vector<TriangleMesh> triangles, std::vector<Light> lights);
    Color intercept(Point3D point, Vector3D);
};

#endif /* SCENE_H */
