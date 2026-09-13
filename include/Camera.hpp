#ifndef CAMERA_HPP
#define CAMERA_HPP

#if defined(__APPLE__)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

enum CameraViewPreset {
    VISTA_PERSPECTIVA = 0,
    VISTA_SUPERIOR = 1,
    VISTA_LATERAL = 2
};

class Camera {
private:
    float yaw;
    float pitch;
    float distance;
    float targetX;
    float targetY;
    float targetZ;
    CameraViewPreset currentPreset;

public:
    Camera();

    void setViewPreset(CameraViewPreset preset);
    void nextViewPreset();
    void rotate(float deltaYaw, float deltaPitch);
    void zoom(float deltaDistance);

    void applyProjection(int width, int height) const;
    void applyView() const;

    CameraViewPreset getPreset() const { return currentPreset; }
};

#endif 