#include "TriangleMesh.h"

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
    for(int i = 0; i < this->triangleVertices.size(); i++) {
        
        Point3D P0 = this->vertices[get<0>(this->triangleVertices[i])];
        Point3D P1 = this->vertices[get<1>(this->triangleVertices[i])];
        Point3D P2 = this->vertices[get<2>(this->triangleVertices[i])];

        Vector3D triangleNormal = this->triangleNormals[i];

        // Step 1: Check if the line intersects the plane of the triangle
        float denom = triangleNormal.dotProduct(vector);

        if (denom == 0) {  // Parallel or coincident
            continue;  // No intersection
        }

        float t = triangleNormal.dotProduct(P0.getVectorToPoint(point)) / denom;

        if (t > 1) {
            // Point is behind screen
            continue;
        }

        vector.multiply(-t);

        Point3D intersectionPoint = point.sumVectorToPoint(vector);
        
        float distance = intersectionPoint.distanceToPoint(point);

        if (distance < interceptionDistance) {
            interceptionDistance = distance;
        }
        else {
            continue;
        }

        // Step 2: Check if the intersection point is inside the triangle
        double denom2 = (P1.y - P2.y)*(P0.x - P2.x) + (P2.x - P1.x)*(P0.y - P2.y);
        double alpha = ((P1.y - P2.y)*(intersectionPoint.x - P2.x) + (P2.x - P1.x)*(intersectionPoint.y - P2.y)) / denom2;
        double beta = ((P2.y - P0.y)*(intersectionPoint.x - P2.x) + (P0.x - P2.x)*(intersectionPoint.y - P2.y)) / denom2;
        double gamma = 1 - alpha - beta;

        const double TOLERANCE = 1e-9;
        if (alpha >= 0 && beta >= 0 && gamma >= 0 && std::abs(alpha + beta + gamma - 1.0) < TOLERANCE) {
            
            // Create the tuple with the point normal vector, intersection point, and mesh
            std::tuple<Vector3D, Point3D, TriangleMesh> tuple(vertexNormals[i], intersectionPoint, *this);

            result = tuple;
        }
        else {
            continue;  // isn't inside the triangle
        }
    }

    return result;
}