#include "Application.hpp"
#include <iostream>

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Application* Application::instance = nullptr;

Application::Application(int width, int height, const char* title, int argc, char** argv)
    : windowWidth(width), windowHeight(height) {
    instance = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(title);

    scene.init();

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialCallback);
}

void Application::displayCallback() {
    if (instance) {
        instance->scene.render(instance->camera);
    }
}

void Application::reshapeCallback(int w, int h) {
    if (instance) {
        instance->windowWidth = w;
        instance->windowHeight = h;
        instance->camera.applyProjection(w, h);
    }
}

void Application::keyboardCallback(unsigned char key, int x, int y) {
    (void)x; (void)y;
    if (!instance) return;

    switch (key) {
        // Rotación jerárquica del brazo
        case '1': instance->scene.rotateBase(-5.0f); break;
        case '2': instance->scene.rotateBase(5.0f); break;
        case '3': instance->scene.rotateShoulder(4.0f); break;
        case '4': instance->scene.rotateShoulder(-4.0f); break;
        case '5': instance->scene.rotateElbow(4.0f); break;
        case '6': instance->scene.rotateElbow(-4.0f); break;

        // Conmutador de vista de cámara (3 vistas predefinidas)
        case 'v':
        case 'V':
            instance->camera.nextViewPreset();
            break;

        // Modo alámbrico (Wireframe)
        case 'w':
        case 'W':
            instance->scene.toggleWireframe();
            break;

        // Zoom de la cámara
        case '+':
        case '=':
            instance->camera.zoom(-0.5f);
            break;
        case '-':
        case '_':
            instance->camera.zoom(0.5f);
            break;

        case 27: // Tecla ESC
            std::exit(0);
            break;
    }
    glutPostRedisplay();
}

void Application::specialCallback(int key, int x, int y) {
    (void)x; (void)y;
    if (!instance) return;

    switch (key) {
        case GLUT_KEY_LEFT:  instance->camera.rotate(-5.0f, 0.0f); break;
        case GLUT_KEY_RIGHT: instance->camera.rotate(5.0f, 0.0f);  break;
        case GLUT_KEY_UP:    instance->camera.rotate(0.0f, 4.0f);  break;
        case GLUT_KEY_DOWN:  instance->camera.rotate(0.0f, -4.0f); break;
    }
    glutPostRedisplay();
}

void Application::run() {
    std::cout << ""
              << " PA2: Laboratorio 3D y Modelado Jerarquico (OpenGL)\n"
              << "\n"
              << " Controles:\n"
              << "  [1 / 2] : Rotar Base del brazo (Eje Y)\n"
              << "  [3 / 4] : Rotar Hombro (Eje Z)\n"
              << "  [5 / 6] : Rotar Codo (Eje Z)\n"
              << "  [V]     : Alternar entre las 3 vistas requeridas\n"
              << "  [W]     : Activar/Desactivar malla Wireframe (Caja)\n"
              << "  [Flechas]: Orbitar camara libremente\n"
              << "  [+ / -] : Zoom camara\n"
              << "  [ESC]   : Salir\n"
              << "" << std::endl;
    glutMainLoop();
}