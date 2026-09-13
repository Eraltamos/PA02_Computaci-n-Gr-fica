#ifndef CURVES_HPP
#define CURVES_HPP

#include <vector>

struct Point3D {
    float x, y, z;
};

class Curves {
public:
    // Curva paramétrica de Bézier cúbica
    static void drawBezierCurve(const std::vector<Point3D>& controlPoints, int segments);

    // Superficie analítica paramétrica de revolución
    static void drawParametricSurface(int uSegments, int vSegments);
};

#endif 