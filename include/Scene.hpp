#ifndef SCENE_HPP
#define SCENE_HPP

#include "Camera.hpp"
#include "Model.hpp"
#include "Curves.hpp"
#include <vector>

class Scene {
private:
    Model importedModel;
    std::vector<Point3D> cableControlPoints;

    // Estados cinemáticos del modelado jerárquico
    float baseAngle;
    float shoulderAngle;
    float elbowAngle;

    // Conmutador alámbrico
    bool wireframeMode;

    // Subrutinas de renderizado por objeto
    void drawFloor();
    void drawTable();
    void drawBench();
    void drawControlBox();
    void drawRobotArm();
    void drawCable();
    void drawParametricSurface();
    void drawImportedModel();

public:
    Scene();

    void init();
    void render(const Camera& camera);

    // Métodos de interacción
    void rotateBase(float delta) { baseAngle += delta; }
    void rotateShoulder(float delta);
    void rotateElbow(float delta);
    void toggleWireframe() { wireframeMode = !wireframeMode; }
};

#endif 