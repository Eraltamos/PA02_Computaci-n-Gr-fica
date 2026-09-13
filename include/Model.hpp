#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <vector>

struct Vertex {
    float x, y, z;
};

struct Face {
    int v1, v2, v3;
};

class Model {
private:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    bool isLoaded;

public:
    Model();

    bool loadOBJ(const std::string& filepath);
    void render() const;

    // Primitivas geométricas 3D reutilizables
    static void drawCube(float sx, float sy, float sz);
    static void drawCylinder(float radius, float height, int slices);
};

#endif 