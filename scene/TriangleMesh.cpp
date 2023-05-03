#include "TriangleMesh.h"
#include <tuple>

float combination(float n, float k);

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

    this->calculateNormals();
}

TriangleMesh::TriangleMesh(
        vector<vector<Point3D>> curves,
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

    vector<Point3D> surfacePoints;

    int n = curves[0].size() - 1;

    // Use Bernstein iteratively to calculate surface points
    for (float t0 = 0.f; t0 <= 1.f; t0 += this->bezierThreshold) {
        vector<Point3D> controlPoints;

        for (auto curvePoints: curves) {
            Point3D controlPoint;

            // Bernstein
            for (int i = 0; i <= n; i++) {
                Point3D point = curvePoints[i];

                point = point.multiply(combination(n, i) * std::pow(t0, i) * std::pow(1 - t0, n - i));

                controlPoint.sumPoint(point);
            }

            controlPoints.push_back(controlPoint);
        }

        for (float t1 = 0.f; t1 <= 1.f; t1 += this->bezierThreshold) {
            Point3D surfacePoint;

            for (int i = 0; i <= n; i++) {
                Point3D controlPoint = controlPoints[i];

                controlPoint = controlPoint.multiply(combination(n, i) * std::pow(t1, i) * std::pow(1 - t1, n - i));

                surfacePoint.sumPoint(controlPoint);
            }

            surfacePoints.push_back(surfacePoint);
        } 
    }

    this->vertices = surfacePoints;

    for (int i = 0; i < surfacePoints.size() - 2; i++) {
        this->triangleVertices.push_back(std::make_tuple(i, i+1, i+2));
    }

    this->calculateNormals();
};

void TriangleMesh::calculateNormals() {
    // initialize vertex normals
    for (int i = 0; i < this->vertices.size(); i++) {
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
        // See https://courses.cs.washington.edu/courses/csep557/10au/lectures/triangle_intersection.pdf
        Point3D P0 = this->vertices[get<0>(this->triangleVertices[i])];
        Point3D P1 = this->vertices[get<1>(this->triangleVertices[i])];
        Point3D P2 = this->vertices[get<2>(this->triangleVertices[i])];

        Vector3D triangleNormal = this->triangleNormals[i];

        // Step 1: Check if the line intersects the plane of the triangle
        float denom = triangleNormal.dotProduct(vector);

        if (denom == 0) {  // Parallel or coincident
            continue;  // No intersection
        }

        Vector3D vectorCameraToPlane = point.getVectorToPoint(P0);
        float numerator = vectorCameraToPlane.dotProduct(triangleNormal);

        float t = numerator / denom;

        if (t <= 1) {
            // is at most behind the screen
            continue;
        }
        
        vector.multiply(t);

        Point3D intersectionPoint = point.sumVectorToPoint(vector);
        
        float distance = intersectionPoint.distanceToPoint(point);

        if (distance >= interceptionDistance) {
            continue;
        }

        // Step 2: Check if the intersection point is inside the triangle
        Vector3D V1 = P0.getVectorToPoint(P1);
        Vector3D V2 = P0.getVectorToPoint(P2);
        Vector3D normal = V1.crossProduct(V2);
        Vector3D P = P0.getVectorToPoint(intersectionPoint);

        // Vector3D C1 = V1.crossProduct(P);
        // Vector3D C2 = V1.crossProduct(P);

        double d00 = V1.dotProduct(V1);
        double d01 = V1.dotProduct(V2);
        double d11 = V2.dotProduct(V2);
        double d20 = P.dotProduct(V1);
        double d21 = P.dotProduct(V2);

        double denom2 = d00 * d11 - d01 * d01;
        
        double beta = (d11 * d20 - d01 * d21) / denom2;
        double gamma = (d00 * d21 - d01 * d20) / denom2;
        double alpha = 1.0 - beta - gamma;
        // float beta = C1.getNorm() / triangleNormal.getNorm();
        // float gamma = C2.getNorm() / triangleNormal.getNorm();
        // float alpha = 1.f - beta - gamma;

        if (alpha >= 0.f && alpha <= 1.f && beta >= 0.f && beta <= 1.f && gamma >= 0.f && gamma <= 1.f) {
            // Create the tuple with the point normal vector, intersection point, and mesh
            Vector3D normalVector;
            Vector3D alphaVector = vertexNormals[get<0>(this->triangleVertices[i])];
            alphaVector.multiply(alpha);

            Vector3D betaVector = vertexNormals[get<1>(this->triangleVertices[i])];
            betaVector.multiply(beta);

            Vector3D gammaVector = vertexNormals[get<2>(this->triangleVertices[i])];
            gammaVector.multiply(gamma);

            normalVector.sumVector(alphaVector);
            normalVector.sumVector(betaVector);
            normalVector.sumVector(gammaVector);
            normalVector.normalize();

            std::tuple<Vector3D, Point3D, TriangleMesh> tuple(normalVector, intersectionPoint, *this);

            result = tuple;

            interceptionDistance = distance;
        }
        else {
            continue;  // isn't inside the triangle
        }
    }

    return result;
}

float combination(float n, float k) {
    if (k == 0 || k == n) {
        return 1;
    } else if (k > n) {
        return 0;
    } else {
        float result = 1;
        for (int i = 1; i <= k; ++i) {
            result *= n - k + i;
            result /= i;
        }
        return result;
    }
}