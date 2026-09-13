#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Model.hpp"

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

Model::Model() : isLoaded(false) {}

bool Model::loadOBJ(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Aviso: No se pudo abrir " << filepath << ". Se utilizara geometria de respaldo." << std::endl;
        return false;
    }

    vertices.clear();
    faces.clear();

    std::string line;
    while (std::getline(file, line)) {
        
        if (line.length() < 2) continue;

        if (line[0] == 'v' && line[1] == ' ') {
            std::istringstream s(line.substr(2));
            Vertex v;
            s >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        } else if (line[0] == 'f' && line[1] == ' ') {
            std::istringstream s(line.substr(2));
            Face f;
            std::string vStr1, vStr2, vStr3;
            s >> vStr1 >> vStr2 >> vStr3;

            auto parseIndex = [](const std::string& str) -> int {
                std::stringstream ss(str);
                std::string item;
                std::getline(ss, item, '/');
                return std::stoi(item) - 1;
            };

            f.v1 = parseIndex(vStr1);
            f.v2 = parseIndex(vStr2);
            f.v3 = parseIndex(vStr3);
            faces.push_back(f);
        }
    }
    isLoaded = !vertices.empty();
    return isLoaded;
}

void Model::render() const {
    if (!isLoaded) {
        drawCube(0.5f, 0.5f, 0.5f);
        return;
    }

    glBegin(GL_TRIANGLES);
    for (const auto& face : faces) {
        const Vertex& vA = vertices[face.v1];
        const Vertex& vB = vertices[face.v2];
        const Vertex& vC = vertices[face.v3];

        
        float ax = vB.x - vA.x, ay = vB.y - vA.y, az = vB.z - vA.z;
        float bx = vC.x - vA.x, by = vC.y - vA.y, bz = vC.z - vA.z;
        float nx = ay * bz - az * by;
        float ny = az * bx - ax * bz;
        float nz = ax * by - ay * bx;
        float length = std::sqrt(nx * nx + ny * ny + nz * nz);
        if (length > 0.0001f) {
            glNormal3f(nx / length, ny / length, nz / length);
        }

        glVertex3f(vA.x, vA.y, vA.z);
        glVertex3f(vB.x, vB.y, vB.z);
        glVertex3f(vC.x, vC.y, vC.z);
    }
    glEnd();
}

void Model::drawCube(float sx, float sy, float sz) {
    float x = sx * 0.5f;
    float y = sy * 0.5f;
    float z = sz * 0.5f;

    glBegin(GL_QUADS);
    // Cara Frontal
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-x, -y,  z); glVertex3f( x, -y,  z);
    glVertex3f( x,  y,  z); glVertex3f(-x,  y,  z);
    // Cara Trasera
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-x, -y, -z); glVertex3f(-x,  y, -z);
    glVertex3f( x,  y, -z); glVertex3f( x, -y, -z);
    // Cara Superior
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-x,  y, -z); glVertex3f(-x,  y,  z);
    glVertex3f( x,  y,  z); glVertex3f( x,  y, -z);
    // Cara Inferior
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-x, -y, -z); glVertex3f( x, -y, -z);
    glVertex3f( x, -y,  z); glVertex3f(-x, -y,  z);
    // Cara Lateral Derecha
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f( x, -y, -z); glVertex3f( x,  y, -z);
    glVertex3f( x,  y,  z); glVertex3f( x, -y,  z);
    // Cara Lateral Izquierda
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-x, -y, -z); glVertex3f(-x, -y,  z);
    glVertex3f(-x,  y,  z); glVertex3f(-x,  y, -z);
    glEnd();
}

void Model::drawCylinder(float radius, float height, int slices) {
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= slices; ++i) {
        float angle = static_cast<float>(i) * 2.0f * static_cast<float>(M_PI) / static_cast<float>(slices);
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);

        glNormal3f(cosA, 0.0f, sinA);
        glVertex3f(radius * cosA, 0.0f, radius * sinA);
        glVertex3f(radius * cosA, height, radius * sinA);
    }
    glEnd();

    // Tapa circular superior
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i < slices; ++i) {
        float angle = static_cast<float>(i) * 2.0f * static_cast<float>(M_PI) / static_cast<float>(slices);
        glVertex3f(radius * std::cos(angle), height, radius * std::sin(angle));
    }
    glEnd();

    // Tapa circular inferior
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, -1.0f, 0.0f);
    for (int i = slices - 1; i >= 0; --i) {
        float angle = static_cast<float>(i) * 2.0f * static_cast<float>(M_PI) / static_cast<float>(slices);
        glVertex3f(radius * std::cos(angle), 0.0f, radius * std::sin(angle));
    }
    glEnd();
}