#include "scene/Light.h"
#include "tools/Color.h"
#include "tools/Point3D.h"
#include "tools/Vector3D.h"
#include "camera/Camera.h"
#include "scene/Sphere.h"
#include "scene/Plane.h"
#include "scene/TriangleMesh.h"
#include "scene/Triangle.h"
#include "scene/Scene.h"

#include <cstddef>
#include <utility>
#include <vector>
#include "iostream"
#include <cmath>
#include <fstream>
#include <string>

vector<Sphere> spheres;
vector<Plane> planes;
vector<Light> lights;
vector<TriangleMesh> trianglesMesh;
Color ambientColor;
Camera camera;

void readFile();
vector<Vector3D> getNormals(vector<Triangle> triangles, vector<Point3D> vertices);

int main() {
    //Lê o arquivo
    readFile();

    //Cria a cena com os objetos lidos do arquivo
    Scene scene = Scene(ambientColor, spheres, planes, trianglesMesh, lights);

    cout << "Scene created" << endl;

    // Raycasting
    ofstream outfile("output.ppm", ios::out | ios::binary);

    int max_value = 255;

    outfile << "P6\n" << camera.screenWidth << " " << camera.screenHeight << "\n" << max_value << "\n";

    // Iterate through screen
    // Height is even
    if (camera.screenHeight % 2 == 0) {
        for (float i = (camera.screenHeight / 2.0) - 1 + 0.5; i > -(camera.screenHeight / 2.0); i--) {
            Vector3D verticalVector = camera.vectorY;
            verticalVector.multiply(i);

            // Width is even
            if (camera.screenWidth % 2 == 0) {
                for (float j = -(camera.screenWidth / 2.0) + 0.5; j < camera.screenWidth / 2.0; j++) {
                    Vector3D horizontalVector = camera.vectorX;
                    horizontalVector.multiply(j);

                    Point3D screenPoint = camera.target.sumVectorToPoint(verticalVector);

                    screenPoint = screenPoint.sumVectorToPoint(horizontalVector);
                    
                    Vector3D cameraToScreen = camera.localization.getVectorToPoint(screenPoint);

                    Color color = scene.intercept(camera.localization, cameraToScreen);

                    outfile << (char)color.red << (char)color.green << (char)color.blue;
                }
            }
            // Width is odd
            else {
                for (float j = ceil(-(camera.screenWidth / 2.0)); j < camera.screenWidth / 2.0; j++) {
                    Vector3D horizontalVector = camera.vectorX;
                    horizontalVector.multiply(j);

                    Point3D screenPoint = camera.target.sumVectorToPoint(verticalVector);

                    screenPoint = screenPoint.sumVectorToPoint(horizontalVector);
                    
                    Vector3D cameraToScreen = camera.localization.getVectorToPoint(screenPoint);

                    Color color = scene.intercept(camera.localization, cameraToScreen);

                    outfile << (char)color.red << (char)color.green << (char)color.blue;
                }
            }
        }
    }
    // Height is odd
    else {
        for (float i = std::ceil(camera.screenHeight / 2.0); i > -camera.screenHeight / 2.0; i--) {
            Vector3D verticalVector = camera.vectorY;
            verticalVector.multiply(i);

            // Width is even
            if (camera.screenWidth % 2 == 0) {
                for (float j = -(camera.screenWidth / 2.0) + 0.5; j < camera.screenWidth / 2.0; j++) {
                    Vector3D horizontalVector = camera.vectorX;
                    horizontalVector.multiply(j);

                    Point3D screenPoint = camera.target.sumVectorToPoint(verticalVector);

                    screenPoint = screenPoint.sumVectorToPoint(horizontalVector);
                    
                    Vector3D cameraToScreen = camera.localization.getVectorToPoint(screenPoint);

                    Color color = scene.intercept(camera.localization, cameraToScreen);

                    outfile << (char)color.red << (char)color.green << (char)color.blue;
                }
            }
            // Width is odd
            else {
                for (float j = ceil(-(camera.screenWidth / 2.0)); j < camera.screenWidth / 2.0; j++) {
                    Vector3D horizontalVector = camera.vectorX;
                    horizontalVector.multiply(j);

                    Point3D screenPoint = camera.target.sumVectorToPoint(verticalVector);

                    screenPoint = screenPoint.sumVectorToPoint(horizontalVector);
                    
                    Vector3D cameraToScreen = camera.localization.getVectorToPoint(screenPoint);

                    Color color = scene.intercept(camera.localization, cameraToScreen);

                    outfile << (char)color.red << (char)color.green << (char)color.blue;
                }
            }
        }
    }

    std::cout << "Done!" << endl;

    outfile.close();

    return 0;
}

void readFile() {
    std::string linha;
    std::ifstream arquivo("scene.txt");
    
    if (arquivo.is_open()) {
        //Lê cada linha do arquivo
        while (std::getline(arquivo, linha)) {
            //Cria as váriaveis comuns a todos os objetos
            float Or, Og, Ob, Kd, Ks, Ka, Kr, Kt, P;
            //Verifica se a linha é uma esfera e adiciona a lista de esferas
            if (linha[0] == 's') {
                float x, y, z, radius;
                sscanf(linha.c_str(), "s %f %f %f %f %f %f %f %f %f %f %f %f %f", &x, &y, &z, &radius, &Or, &Og, &Ob, &Kd, &Ks, &Ka, &Kr, &Kt, &P);
                spheres.push_back(Sphere(Point3D(x, y, z), radius, Color(Or, Og, Ob), Kd, Ks, Ka, Kr, Kt, P));
            }
            //Verifica se a linha é um plano e adiciona a lista de planos
            if (linha[0] == 'p') {
                float px, py, pz, vx, vy, vz;
                sscanf(linha.c_str(), "p %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &px, &py, &pz, &vx, &vy, &vz, &Or, &Og, &Ob, &Kd, &Ks, &Ka, &Kr, &Kt, &P);
                planes.push_back(Plane(Point3D(px, py, pz), Vector3D(vx, vy, vz), Color(Or, Og, Ob), Kd, Ks, Ka, Kr, Kt, P));
            }
            //Verifica se a linha é uma Malha de Triângulos e adiciona a lista de Malhas de Triângulos
            if (linha[0] == 't') {
                int nt, nv;
                sscanf(linha.c_str(), "t %d %d", &nt, &nv);
                vector<Point3D> vertices;
                vector<Triangle> triangles;
                //Lê os vértices
                for (int i = 0; i < nv; i++) {
                    std::getline(arquivo, linha);
                    int v1, v2, v3;
                    sscanf(linha.c_str(), "%d %d %d", &v1, &v2, &v3);
                    vertices.push_back(Point3D(v1, v2, v3));
                    
                }
                //Lê os triangulos
                for (int i = 0; i < nt; i++) {
                    std::getline(arquivo, linha);
                    float x, y, z;
                    sscanf(linha.c_str(), "%f %f %f", &x, &y, &z);
                    triangles.push_back(Triangle(vertices[x], vertices[y], vertices[z]));
                }
                //Lê as propriedades do material
                sscanf(linha.c_str(), "%f %f %f %f %f %f %f %f %f", &Or, &Og, &Ob, &Kd, &Ks, &Ka, &Kr, &Kt, &P);
                //Calcula as normais dos triangulos e dos vertices
                vector<Vector3D> vertexNormals, triangleNormals = getNormals(triangles, vertices);
                //Adiciona a malha de triangulos a lista de malhas de triangulos
                trianglesMesh.push_back(TriangleMesh(nt, nv, vertices, triangles, triangleNormals, vertexNormals, Color(Or, Og, Ob), Kd, Ks, Ka, Kr, Kt, P));

            }
            //Verifica se a linha é uma camera e cria a camera
            if (linha[0] == 'c') {
                int hres, vres;
                float d, upx, upy, upz, Cx, Cy, Cz, Mx, My, Mz;
                sscanf(linha.c_str(), "c %d %d %f %f %f %f %f %f %f %f %f %f", &hres, &vres, &d, &upx, &upy, &upz, &Cx, &Cy, &Cz, &Mx, &My, &Mz);
                camera = Camera(hres, vres, d, Vector3D(upx, upy, upz), Point3D(Cx, Cy, Cz), Point3D(Mx, My, Mz));
            }
            //Verifica se a linha é uma luz e adiciona a lista de luzes
            if (linha[0] == 'l') {
                float x, y, z, Ilr, Ilg, Ilb;
                sscanf(linha.c_str(), "l %f %f %f %f %f %f", &x, &y, &z, &Ilr, &Ilg, &Ilb);
                lights.push_back(Light(Point3D(x, y, z), Color(Ilr, Ilg, Ilb)));
            }
            //Verifica se a linha é a cor ambiente e cria a cor ambiente
            if (linha[0] == 'a') {
                float Ir, Ig, Ib;
                sscanf(linha.c_str(), "a %f %f %f", &Ir, &Ig, &Ib);
                ambientColor = Color(Ir, Ig, Ib);
            }
        }
        //Fecha o arquivo
        arquivo.close();
        
        
    }

    else std::cout << "Unable to open file";

}

vector<Vector3D> getNormals(vector<Triangle> triangles, vector<Point3D> vertices) {
    vector<Vector3D> triangleNormals, vertexNormals;
    //Cria um array de normais de triangulos
    for (int i = 0; i < triangles.size(); i++) {
        Vector3D v1 = triangles[i].p1.getVectorToPoint(triangles[i].p2);
        Vector3D v2 = triangles[i].p1.getVectorToPoint(triangles[i].p3);
        Vector3D normal = v1.crossProduct(v2);
        normal.normalize();
        triangleNormals.push_back(normal);
    }
    for (int i = 0; i < vertices.size(); i++) {
        //Cria um array de normais de vertices onde cada normal é a média das normais dos triangulos que o contem
        Vector3D normal = Vector3D(0, 0, 0);
        int count = 0;
        for (int j = 0; j < triangles.size(); j++) {
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
    return vertexNormals, triangleNormals;
}