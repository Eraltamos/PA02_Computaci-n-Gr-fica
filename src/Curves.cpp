#define _USE_MATH_DEFINES
#include <cmath>
#include "Curves.hpp"

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void Curves::drawBezierCurve(const std::vector<Point3D>& cp, int segments) {
    if (cp.size() < 4) return;

    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(segments);
        float u = 1.0f - t;
        float b0 = u * u * u;
        float b1 = 3.0f * u * u * t;
        float b2 = 3.0f * u * t * t;
        float b3 = t * t * t;

        float x = b0 * cp[0].x + b1 * cp[1].x + b2 * cp[2].x + b3 * cp[3].x;
        float y = b0 * cp[0].y + b1 * cp[1].y + b2 * cp[2].y + b3 * cp[3].y;
        float z = b0 * cp[0].z + b1 * cp[1].z + b2 * cp[2].z + b3 * cp[3].z;

        glVertex3f(x, y, z);
    }
    glEnd();
    glLineWidth(1.0f);
}

void Curves::drawParametricSurface(int uSegments, int vSegments) {
    for (int i = 0; i < uSegments; ++i) {
        float u1 = static_cast<float>(i) / static_cast<float>(uSegments);
        float u2 = static_cast<float>(i + 1) / static_cast<float>(uSegments);

        float r1 = 0.15f + 0.65f * u1;
        float y1 = 0.50f * (u1 * u1);
        float r2 = 0.15f + 0.65f * u2;
        float y2 = 0.50f * (u2 * u2);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= vSegments; ++j) {
            float v = static_cast<float>(j) * 2.0f * static_cast<float>(M_PI) / static_cast<float>(vSegments);
            float cosV = std::cos(v);
            float sinV = std::sin(v);

            glNormal3f(cosV, 0.5f, sinV);
            glVertex3f(r1 * cosV, y1, r1 * sinV);
            glVertex3f(r2 * cosV, y2, r2 * sinV);
        }
        glEnd();
    }
}