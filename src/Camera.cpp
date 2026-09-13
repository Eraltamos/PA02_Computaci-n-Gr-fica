#define _USE_MATH_DEFINES
#include <cmath>
#include "Camera.hpp"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

Camera::Camera()
    : yaw(45.0f), pitch(30.0f), distance(12.0f),
      targetX(0.0f), targetY(1.0f), targetZ(0.0f),
      currentPreset(VISTA_PERSPECTIVA) {}

void Camera::setViewPreset(CameraViewPreset preset) {
    currentPreset = preset;
    switch (preset) {
        case VISTA_PERSPECTIVA:
            yaw = 45.0f;
            pitch = 30.0f;
            distance = 12.0f;
            break;
        case VISTA_SUPERIOR:
            yaw = 0.0f;
            pitch = 89.9f;
            distance = 14.0f;
            break;
        case VISTA_LATERAL:
            yaw = 90.0f;
            pitch = 0.0f;
            distance = 12.0f;
            break;
    }
}

void Camera::nextViewPreset() {
    int next = (static_cast<int>(currentPreset) + 1) % 3;
    setViewPreset(static_cast<CameraViewPreset>(next));
}

void Camera::rotate(float deltaYaw, float deltaPitch) {
    yaw += deltaYaw;
    pitch += deltaPitch;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}

void Camera::zoom(float deltaDistance) {
    distance += deltaDistance;
    if (distance < 3.0f) distance = 3.0f;
    if (distance > 30.0f) distance = 30.0f;
}

void Camera::applyProjection(int width, int height) const {
    if (height == 0) height = 1;
    float aspect = static_cast<float>(width) / static_cast<float>(height);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);
}

void Camera::applyView() const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float radYaw = yaw * static_cast<float>(M_PI) / 180.0f;
    float radPitch = pitch * static_cast<float>(M_PI) / 180.0f;

    float eyeX = targetX + distance * std::cos(radPitch) * std::sin(radYaw);
    float eyeY = targetY + distance * std::sin(radPitch);
    float eyeZ = targetZ + distance * std::cos(radPitch) * std::cos(radYaw);

    float upY = 1.0f;
    if (pitch > 89.0f) upY = 0.0f;

    gluLookAt(eyeX, eyeY, eyeZ,
              targetX, targetY, targetZ,
              0.0f, upY, (pitch > 89.0f ? -1.0f : 0.0f));
}