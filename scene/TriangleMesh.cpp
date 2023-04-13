#include "TriangleMesh.h"
#include "../tools/Point3D.h"
#include "../tools/Vector3D.h"
#include "../tools/Color.h"
#include "../tools/Matrix4X4.h"
#include "../tools/MatrixOperations.h"
#include <cstddef>
#include <vector>
#include <limits>
#include <optional>

using namespace std;

TriangleMesh::TriangleMesh() {}

TriangleMesh::TriangleMesh(
        int numTriangles, 
        int numVertices, 
        vector<Point3D> vertices,
        vector<vector<int>> trianglesIdxs, 
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
    this->trianglesIdxs = trianglesIdxs;
    this->color = color;
    this->diffuseCoefficient = diffuseCoefficient;
    this->specularCoefficient = specularCoefficient;
    this->ambientCoefficient = ambientCoefficient;
    this->reflectionCoefficient = reflectionCoefficient;
    this->transmissionCoefficient = transmissionCoefficient;
    this->rugosityCoefficient = rugosityCoefficient;

    this->updateMesh();

}


void TriangleMesh::updateMesh() {

    vector<Triangle> triangles;

    for (int i = 0; i < this->numTriangles - 1; i++) {
        triangles.push_back(Triangle(this->vertices.at(
                this->trianglesIdxs.at(i).at(0)), 
                this->vertices.at(
                this->trianglesIdxs.at(i).at(1)), 
                this->vertices.at(
                this->trianglesIdxs.at(i).at(2))
        ));
    }

    this->triangles = triangles;

    std::optional<std::pair<vector<Vector3D>, vector<Vector3D>>> normals = this->getNormals(this->triangles, this->vertices);

    this->vertexNormals = normals.value().first;
    this->triangleNormals = normals.value().second;
}

std::optional<std::pair<vector<Vector3D>, vector<Vector3D>>> TriangleMesh::getNormals(vector<Triangle> triangles, vector<Point3D> vertices) {
    std::optional<std::pair<vector<Vector3D>, vector<Vector3D>>> pair;
    vector<Vector3D> triangleNormals, vertexNormals;
    //Cria um array de normais de triangulos
    for (int i = 0; i < triangles.size() - 1; i++) {
        Vector3D v1 = triangles[i].p1.getVectorToPoint(triangles[i].p2);
        Vector3D v2 = triangles[i].p1.getVectorToPoint(triangles[i].p3);
        Vector3D normal = v1.crossProduct(v2);
        normal.normalize();
        triangleNormals.push_back(normal);
    }
    for (int i = 0; i < vertices.size() - 1; i++) {
        //Cria um array de normais de vertices onde cada normal é a média das normais dos triangulos que o contem
        Vector3D normal = Vector3D(0, 0, 0);
        int count = 0;
        for (int j = 0; j < triangles.size() - 1; j++) {
            if (triangles[j].p1.x == vertices[i].x && triangles[j].p1.y == vertices[i].y && triangles[j].p1.z == vertices[i].z
                || triangles[j].p2.x == vertices[i].x && triangles[j].p2.y == vertices[i].y && triangles[j].p2.z == vertices[i].z
                || triangles[j].p3.x == vertices[i].x && triangles[j].p3.y == vertices[i].y && triangles[j].p3.z == vertices[i].z) 
                {
                normal.x += triangleNormals[j].x;
                normal.y += triangleNormals[j].y;
                normal.z += triangleNormals[j].z;
                count++;
            }
        }
        normal.multiply(1.0 / count);
        normal.normalize();
        vertexNormals.push_back(normal);
    }

    pair = std::make_pair(vertexNormals, triangleNormals);
    return pair;
}

std::optional<std::pair<Triangle, Point3D>> TriangleMesh::intercept(Point3D point, Vector3D vector) {
    float t_min = std::numeric_limits<float>::max(); // minimum distance to intersection

    std::optional<std::pair<Triangle, Point3D>> pair;

    // Iterate over all triangles in the mesh
    for (int i = 0; i < numTriangles - 1; i++) {
        Triangle triangle = triangles[i];
        
        // Check if the ray intersects the plane of the triangle
        Point3D plane_intersect = triangle.interceptToPlane(point, vector);
        
        if (!triangle.isInsideTriangle(plane_intersect)) {
            continue; // skip to next triangle
        }
        
        // Check if the intersection point is in front of the screen
        if ((plane_intersect.x - point.x) / vector.x <= 1 || (plane_intersect.y - point.y) / vector.y <= 1 || (plane_intersect.z - point.z) / vector.z <= 1) {
            continue;
        }

        // Calculate the distance to the intersection point
        float t = point.distanceToPoint(plane_intersect);
        
        // Check if this is the closest intersection point so far
        if (t < t_min) {
            t_min = t;

            pair = std::make_pair(triangle, plane_intersect);
        }
    }

    return pair;
}
 void TriangleMesh::translade(float x, float y, float z) {
    vector<Point3D> transladedVertices;

    Matrix4X4 translationMatrix;
    translationMatrix.toTranslationMatrix(x, y, z);
    

    for (int i=0; i<this->vertices.size() - 1; i++){
        Point3D cur_vertix = this->vertices.at(i);
        cur_vertix = pointMatrixMultiplication(cur_vertix.x, cur_vertix.y, cur_vertix.z, translationMatrix);
         
        transladedVertices.push_back(cur_vertix);
    }
    this->vertices = transladedVertices;
    this->updateMesh();
 }

void TriangleMesh::rotate(double angle, char axis) {
    vector<Point3D> rotatedVertices;

    Point3D center = this->getMeshCenter();

    Matrix4X4 transladeCenter, transladeBack, rotation;

    transladeCenter.toTranslationMatrix(-center.x, -center.y, -center.z);
    rotation.toRotationMatrix(angle, axis);
    transladeBack.toTranslationMatrix(center.x, center.y, center.z);

    for (int i=0; i<this->vertices.size() - 1; i++){
        Point3D cur_vertix = this->vertices.at(i);
        cur_vertix = pointMatrixMultiplication(cur_vertix.x, cur_vertix.y, cur_vertix.z, transladeCenter);
        cur_vertix = pointMatrixMultiplication(cur_vertix.x, cur_vertix.y, cur_vertix.z, rotation);
        cur_vertix = pointMatrixMultiplication(cur_vertix.x, cur_vertix.y, cur_vertix.z, transladeBack);
        
        rotatedVertices.push_back(cur_vertix);
    }
    this->vertices = rotatedVertices;
    this->updateMesh();
}

Point3D TriangleMesh::getMeshCenter() {
    float x=0;
    float y=0;
    float z=0;

    for (int i=0; i<this->vertices.size() - 1; i++){
        x += this->vertices.at(i).x;
        y += this->vertices.at(i).y;
        z += this->vertices.at(i).z;
    }
    x /= this->vertices.size();
    y /= this->vertices.size();
    z /= this->vertices.size();

    return Point3D(x, y, z);
}