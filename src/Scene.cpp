#include "Scene.hpp"

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Scene::Scene()
    : baseAngle(25.0f), shoulderAngle(40.0f), elbowAngle(-50.0f),
      wireframeMode(false) {}

void Scene::init() {
    // Configuracion iluminacion fija
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat lightPos[] = { 5.0f, 10.0f, 7.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat lightDiffuse[] = { 0.85f, 0.85f, 0.85f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    // Carga de la malla poligonal externa
    importedModel.loadOBJ("assets/models/modelo.obj");

    // Puntos de control para la curva parametrica de Bezier cubica - Cable
    cableControlPoints = {
        { 1.8f, 1.2f, -0.4f },   // Salida de la caja de control
        { 1.0f, 2.8f, -0.2f },   // Elevacion intermedia
        {-0.5f, 2.2f,  0.2f },   // Suspension curva
        {-1.2f, 1.1f,  0.0f }    // Conexion con la base del brazo
    };
}

void Scene::rotateShoulder(float delta) {
    shoulderAngle += delta;
    if (shoulderAngle > 85.0f) shoulderAngle = 85.0f;
    if (shoulderAngle < -15.0f) shoulderAngle = -15.0f;
}

void Scene::rotateElbow(float delta) {
    elbowAngle += delta;
    if (elbowAngle > 10.0f) elbowAngle = 10.0f;
    if (elbowAngle < -120.0f) elbowAngle = -120.0f;
}

// Suelo del laboratorio
void Scene::drawFloor() {
    glColor3f(0.40f, 0.42f, 0.45f);
    glPushMatrix();
        glTranslatef(0.0f, -0.05f, 0.0f);
        Model::drawCube(16.0f, 0.1f, 16.0f);
    glPopMatrix();
}

// Mesa de trabajo
void Scene::drawTable() {
    // Tablero superior
    glColor3f(0.68f, 0.38f, 0.15f);
    glPushMatrix();
        glTranslatef(0.0f, 0.95f, 0.0f);
        Model::drawCube(5.0f, 0.1f, 2.2f);
    glPopMatrix();

    // Patas de soporte
    glColor3f(0.50f, 0.25f, 0.08f);
    float legX[4] = { -2.3f,  2.3f, -2.3f,  2.3f };
    float legZ[4] = { -0.9f, -0.9f,  0.9f,  0.9f };
    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
            glTranslatef(legX[i], 0.45f, legZ[i]);
            Model::drawCube(0.18f, 0.9f, 0.18f);
        glPopMatrix();
    }
}

// Banco
void Scene::drawBench() {
    glColor3f(0.25f, 0.25f, 0.28f);
    glPushMatrix();
        glTranslatef(2.2f, 0.35f, 1.8f);
        Model::drawCube(1.8f, 0.08f, 0.6f);
    glPopMatrix();

    float bLegX[4] = { 1.4f, 3.0f, 1.4f, 3.0f };
    float bLegZ[4] = { 1.6f, 1.6f, 2.0f, 2.0f };
    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
            glTranslatef(bLegX[i], 0.16f, bLegZ[i]);
            Model::drawCube(0.08f, 0.32f, 0.08f);
        glPopMatrix();
    }
}

// Modulo de control
void Scene::drawControlBox() {
    glPushMatrix();
        glTranslatef(1.8f, 1.35f, -0.4f);
        if (wireframeMode) {
            glDisable(GL_LIGHTING); 
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(0.0f, 0.85f, 0.95f); 
        } else {
            glColor3f(0.12f, 0.20f, 0.28f);
        }

        Model::drawCube(0.8f, 0.7f, 0.9f);

        if (wireframeMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_LIGHTING); 
        }
    glPopMatrix();
}

// Brazo Robotico - Cadena de Modelado Jerarquico
void Scene::drawRobotArm() {
    glPushMatrix();
        // Base giratoria sobre la mesa - Rotacion en Y
        glTranslatef(-1.2f, 1.0f, 0.0f);
        glRotatef(baseAngle, 0.0f, 1.0f, 0.0f);

        // Base cilindrica
        glColor3f(0.15f, 0.35f, 0.75f);
        Model::drawCylinder(0.55f, 0.25f, 24);

        // Hombro - Rotacion en Z 
        glTranslatef(0.0f, 0.25f, 0.0f);
        glRotatef(shoulderAngle, 0.0f, 0.0f, 1.0f);

        // Eslabon inferior
        glColor3f(0.95f, 0.55f, 0.10f);
        glPushMatrix();
            glTranslatef(0.0f, 0.8f, 0.0f);
            Model::drawCube(0.24f, 1.6f, 0.24f);
        glPopMatrix();

        // Codo (Hereda transformaciones previas)
        glTranslatef(0.0f, 1.6f, 0.0f);
        glRotatef(elbowAngle, 0.0f, 0.0f, 1.0f);

        // Eslabon superior
        glColor3f(0.90f, 0.80f, 0.15f);
        glPushMatrix();
            glTranslatef(0.0f, 0.6f, 0.0f);
            Model::drawCube(0.18f, 1.2f, 0.18f);
        glPopMatrix();

        // Pinzas mecanicas
        glColor3f(0.2f, 0.2f, 0.2f);
        glPushMatrix();
            glTranslatef(-0.1f, 1.3f, 0.0f);
            Model::drawCube(0.05f, 0.2f, 0.12f);
            glTranslatef(0.2f, 0.0f, 0.0f);
            Model::drawCube(0.05f, 0.2f, 0.12f);
        glPopMatrix();

    glPopMatrix(); 
}

// Cable de alimentacion - Curva de Bezier con proteccion luminica
void Scene::drawCable() {
    glDisable(GL_LIGHTING);
    glColor3f(0.05f, 0.05f, 0.05f);
    Curves::drawBezierCurve(cableControlPoints, 32);
    glEnable(GL_LIGHTING); 
}

// Superficie Parametrica Analitica de Revolucion
void Scene::drawParametricSurface() {
    glColor3f(0.10f, 0.75f, 0.85f);
    glPushMatrix();
        glTranslatef(1.8f, 1.70f, -0.4f);
        Curves::drawParametricSurface(16, 24);
    glPopMatrix();
}

// Objeto importado desde modelo.obj
void Scene::drawImportedModel() {
    glColor3f(0.75f, 0.20f, 0.25f);
    glPushMatrix();
        glTranslatef(0.2f, 1.0f, 0.6f); 
        glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
        glScalef(0.8f, 0.8f, 0.8f);    
        importedModel.render();
    glPopMatrix();
}

void Scene::render(const Camera& camera) {
    glClearColor(0.85f, 0.88f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.applyView();

    drawFloor();
    drawTable();
    drawBench();
    drawControlBox();
    drawRobotArm();
    drawCable();
    drawParametricSurface();
    drawImportedModel();

    glutSwapBuffers();
}