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


int main() {
    std::string linha;
    std::ifstream arquivo("scene.txt");

    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            float Or, Og, Ob, Kd, Ks, Ka, Kr, Kt, P;
            std::cout << linha << std::endl;
            if (linha[0] == 's') {
                float x, y, z, radius;
                sscanf(linha.c_str(), "s %f %f %f %f %f %f %f %f %f %f %f %f %f", &x, &y, &z, &radius, &Or, &Og, &Ob, &Kd, &Ks, &Ka, &Kr, &Kt, &P);
            }
            if (linha[0] == 'p') {
                float px, py, pz, vx, vy, vz;
                sscanf(linha.c_str(), "p %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &px, &py, &pz, &vx, &vy, &vz, &Or, &Og, &Ob, &Kd, &Ks, &Ka, &Kr, &Kt, &P);
            }
            if (linha[0] == 't') {
                int nt, nv;
                sscanf(linha.c_str(), "t %d %d", &nt, &nv);
                for (int i = 0; i < nv; i++) {
                    std::getline(arquivo, linha);
                    int v1, v2, v3;
                    sscanf(linha.c_str(), "%d %d %d", &v1, &v2, &v3);
                }
                for (int i = 0; i < nt; i++) {
                    std::getline(arquivo, linha);
                    float x, y, z;
                    sscanf(linha.c_str(), "%f %f %f", &x, &y, &z);
                }
            }
            if (linha[0] == 'c') {
                int hres, vres;
                float d, upx, upy, upz, Cx, Cy, Cz, Mx, My, Mz;
                sscanf(linha.c_str(), "c %d %d %f %f %f %f %f %f %f %f %f %f", &hres, &vres, &d, &upx, &upy, &upz, &Cx, &Cy, &Cz, &Mx, &My, &Mz);
            }
            if (linha[0] == 'l') {
                float x, y, z, Ilr, Ilg, Ilb;
                sscanf(linha.c_str(), "l %f %f %f %f %f %f", &x, &y, &z, &Ilr, &Ilg, &Ilb);
            }
            if (linha[0] == 'a') {
                float Ir, Ig, Ib;
                sscanf(linha.c_str(), "a %f %f %f", &Ir, &Ig, &Ib);
            }
        }
        arquivo.close();
    }

    else std::cout << "Unable to open file";

}





/*
int main () {

    vector<Sphere> spheres;
    spheres.push_back(Sphere(Point3D(0, 0, 10), 2, Color(200, 0, 200), 0, 0, 0, 0, 0, 0));

    vector<Plane> planes;
    planes.push_back(Plane(Point3D(0, 0, 20), Vector3D(0, 0, -1), Color(100, 100, 255), 0, 0, 0, 0, 0, 0));

    vector<Light> lights;

    vector<TriangleMesh> triangles;

    Scene scene = Scene(Color(1, 1, 1), spheres, planes, triangles, lights);

    Color color1 = scene.intercept(Point3D(0, 0, 0), Vector3D(0, 0, 11.9));

    std::cout << color1.red << " " << color1.green << " " << color1.blue << "\n";
}*/