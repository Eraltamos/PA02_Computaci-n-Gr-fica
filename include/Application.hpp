#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Camera.hpp"
#include "Scene.hpp"

class Application {
private:
    static Application* instance;

    int windowWidth;
    int windowHeight;
    Camera camera;
    Scene scene;

    // Callbacks estáticos para GLUT
    static void displayCallback();
    static void reshapeCallback(int w, int h);
    static void keyboardCallback(unsigned char key, int x, int y);
    static void specialCallback(int key, int x, int y);

public:
    Application(int width, int height, const char* title, int argc, char** argv);
    void run();

    Camera& getCamera() { return camera; }
    Scene& getScene() { return scene; }
};

#endif