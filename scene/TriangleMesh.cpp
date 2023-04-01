#include "TriangleMesh.h"
#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"
#include "../tools/Color.h"
#include <vector>
using namespace std;

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
    this->diffuseCoefficient = diffuseCoefficient;
    this->specularCoefficient = specularCoefficient;
    this->ambientCoefficient = ambientCoefficient;
    this->reflectionCoefficient = reflectionCoefficient;
    this->transmissionCoefficient = transmissionCoefficient;
    this->rugosityCoefficient = rugosityCoefficient;
    
}

Point3D TriangleMesh::intercept(Point3D point, Vector3D vector) {
    float t_min = INFINITY; // minimum distance to intersection
    Point3D intersect_point; // intersection point
    bool has_intersection = false; // flag to indicate if an intersection was found
    
    // Iterate over all triangles in the mesh
    for (int i = 0; i < numTriangles; i++) {
        Triangle triangle = triangles[i];
        
        // Check if the ray intersects the plane of the triangle
        Point3D plane_intersect = triangle.interceptToPlane(point, vector);
        if (!triangle.isInsideTriangle(plane_intersect)) {
            continue; // skip to next triangle
        }
        
        // Calculate the distance to the intersection point
        float t = point.distanceToPoint(plane_intersect);
        
        // Check if this is the closest intersection point so far
        if (t < t_min) {
            t_min = t;
            intersect_point = plane_intersect;
            has_intersection = true;
        }
    }
    
    // If an intersection was found, return the intersection point
    if (has_intersection) {
        return intersect_point;
    }
}