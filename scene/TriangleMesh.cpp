#include "TriangleMesh.h"

using namespace std;

TriangleMesh::TriangleMesh () {};
TriangleMesh::TriangleMesh(
        vector<Point3D> vertices,
        vector<std::tuple<int, int, int>> triangleVertices,
        Color color,
        float diffuseCoefficient, 
        float specularCoefficient,
        float ambientCoefficient,
        float reflectionCoefficient,
        float transmissionCoefficient,
        float rugosityCoefficient) {

    this->color = color;
    this->color.normalize();
    this->diffuseCoefficient = diffuseCoefficient;
    this->specularCoefficient = specularCoefficient;
    this->ambientCoefficient = ambientCoefficient;
    this->reflectionCoefficient = reflectionCoefficient;
    this->transmissionCoefficient = transmissionCoefficient;
    this->rugosityCoefficient = rugosityCoefficient;

    this->vertices = vertices;
    this->triangleVertices = triangleVertices;

    // initialize vertex normals
    for (int i = 0; i < vertices.size(); i++) {
        this->vertexNormals.push_back(Vector3D());
    }
    // get triangles' normals
    for (auto t: this->triangleVertices) {
        Vector3D v1 = this->vertices[get<0>(t)].getVectorToPoint(this->vertices[get<1>(t)]);
        Vector3D v2 = this->vertices[get<0>(t)].getVectorToPoint(this->vertices[get<2>(t)]);

        Vector3D normal = v1.crossProduct(v2);
        normal.normalize();

        // make normal point outwards
        Point3D barycenter = Point3D();
        barycenter.sumPoint(this->vertices[get<0>(t)]);
        barycenter.sumPoint(this->vertices[get<1>(t)]);
        barycenter.sumPoint(this->vertices[get<2>(t)]);

        barycenter.x /= 3.f; barycenter.y /= 3.f; barycenter.z /= 3.f;

        Vector3D barycenterToVertex = barycenter.getVectorToPoint(this->vertices[get<0>(t)]);

        if (barycenterToVertex.dotProduct(normal) < 0) {
            normal.multiply(-1);
        }

        this->triangleNormals.push_back(normal);
    }

    // sum triangles normals to vertex normals
    for (int i = 0; i < triangleVertices.size(); i++) {
        this->vertexNormals[get<0>(this->triangleVertices[i])].sumVector(this->triangleNormals[i]);
        this->vertexNormals[get<1>(this->triangleVertices[i])].sumVector(this->triangleNormals[i]);
        this->vertexNormals[get<2>(this->triangleVertices[i])].sumVector(this->triangleNormals[i]);
    }

    // normalize all vertex normals
    for (auto &v: this->vertexNormals) {
        v.normalize();
    }
}

std::optional<std::tuple<Vector3D, Point3D, TriangleMesh>> TriangleMesh::intercept(Point3D point, Vector3D vector) {
    float interceptionDistance = std::numeric_limits<float>::max(); // minimum distance to intersection

    std::optional<std::tuple<Vector3D, Point3D, TriangleMesh>> result = std::nullopt;

    // Iterate over all triangles in the mesh
    for (int i = 0; i < this->triangleVertices.size(); i++) {
        Point3D P0 = this->vertices[get<0>(this->triangleVertices[i])];
        Point3D P1 = this->vertices[get<1>(this->triangleVertices[i])];
        Point3D P2 = this->vertices[get<2>(this->triangleVertices[i])];
        
        Vector3D triangleNormal = this->triangleNormals[i];

        // Step 1: Check if the line intersects the plane of the triangle
        float denom = triangleNormal.dotProduct(vector);

        if (denom == 0) {  // Parallel or coincident
            continue;  // No intersection
        }

        float t = -(triangleNormal.dotProduct(P0.getVectorToPoint(point))) / denom;

        if (t <= 1) {
            // Point is behind screen
            continue;
        }

        vector.multiply(t);

        Point3D intersectionPoint = point.sumVectorToPoint(vector);
        
        float distance = intersectionPoint.distanceToPoint(point);

        if (distance < interceptionDistance) {
            interceptionDistance = distance;
        }
        else {
            continue;
        }

        // Step 2: Check if the intersection point is inside the triangle
        Vector3D v0 = P0.getVectorToPoint(P1);
        Vector3D v1 = P0.getVectorToPoint(P2);
        Vector3D v2 = P0.getVectorToPoint(intersectionPoint);

        float d00 = v0.dotProduct(v0);
        float d01 = v0.dotProduct(v1);
        float d11 = v1.dotProduct(v1);
        float d20 = v2.dotProduct(v0);
        float d21 = v2.dotProduct(v1);

        float denom2 = d00 * d11 - d01 * d01;

        float alpha = (d11 * d20 - d01 * d21) / denom2;
        float beta = (d00 * d21 - d01 * d20) / denom2;
        float gamma = 1.0f - alpha - beta;

        if (alpha >= 0 && beta >= 0 && gamma >= 0 && (alpha + beta + gamma) == 1) {
            // Get the interception point normal
            Vector3D N0 = vertexNormals[get<0>(this->triangleVertices[i])];
            N0.multiply(alpha);

            Vector3D N1 = vertexNormals[get<1>(this->triangleVertices[i])];
            N1.multiply(beta);

            Vector3D N2 = vertexNormals[get<2>(this->triangleVertices[i])];
            N2.multiply(gamma);

            Vector3D vertexNormal;
            vertexNormal.sumVector(N0);
            vertexNormal.sumVector(N1);
            vertexNormal.sumVector(N2);
            vertexNormal.normalize();

            // Create the tuple with the point normal vector, intersection point, and mesh
            std::tuple<Vector3D, Point3D, TriangleMesh> tuple(vertexNormal, intersectionPoint, *this);

            result = tuple;
        }
        else {
            continue;  // isn't inside the triangle
        }
    }

    return result;
}