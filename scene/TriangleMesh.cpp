#include "TriangleMesh.h"
#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"
#include "../tools/Color.h"
#include <tuple>
#include <iostream>

using namespace std;

TriangleMesh::TriangleMesh () {};
TriangleMesh::TriangleMesh(
        int numTriangles, 
        int numVertices, 
        vector<Point3D> vertices,
        vector<Triangle> triangles,
        vector<Vector3D> triangleNormals,
        vector<Vector3D> vertexNormals, 
        Color color,
        float diffuseCoefficient, 
        float specularCoefficient,
        float ambientCoefficient,
        float reflectionCoefficient,
        float transmissionCoefficient,
        float rugosityCoefficient) {

    this->numTriangles = numTriangles;
    this->numVertices = numVertices;
    this->vertices = vertices;
    this->triangles = triangles;
    this->triangleNormals = triangleNormals;
    this->vertexNormals = vertexNormals;
    this->color = color;
    this->color.normalize();
    this->diffuseCoefficient = diffuseCoefficient;
    this->specularCoefficient = specularCoefficient;
    this->ambientCoefficient = ambientCoefficient;
    this->reflectionCoefficient = reflectionCoefficient;
    this->transmissionCoefficient = transmissionCoefficient;
    this->rugosityCoefficient = rugosityCoefficient;
}

std::optional<std::tuple<Triangle, Point3D, TriangleMesh>> TriangleMesh::intercept(Point3D point, Vector3D vector) {
    float t_min = std::numeric_limits<float>::max(); // minimum distance to intersection

    std::optional<std::tuple<Triangle, Point3D, TriangleMesh>> result = std::nullopt;

    // Iterate over all triangles in the mesh
    for (int i = 0; i < numTriangles; i++) {
        Triangle triangle = triangles[i];
        
        // Check if the ray intersects the plane of the triangle
        auto plane_intersect = triangle.intercept(point, vector);

        if (!plane_intersect) {
            continue;
        }
        // Point3D plane_intersect = triangle.interceptToPlane(point, vector);
        
        // if (!triangle.isInsideTriangle(plane_intersect)) {
        //     continue; // skip to next triangle
        // }
        
        // // Check if the intersection point is in front of the screen
        // if ((plane_intersect.x - point.x) / vector.x <= 1 || (plane_intersect.y - point.y) / vector.y <= 1 || (plane_intersect.z - point.z) / vector.z <= 1) {
        //     continue;
        // }

        // Calculate the distance to the intersection point
        float t = point.distanceToPoint(plane_intersect.value());
        
        // Check if this is the closest intersection point so far
        if (t < t_min) {
            t_min = t;

            // Create the tuple with the triangle, intersection point, and mesh
            std::tuple<Triangle, Point3D, TriangleMesh> tuple(triangle, plane_intersect.value(), *this);

            result = tuple;
        }
    }

    return result;
}