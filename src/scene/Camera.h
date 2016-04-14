//
// Created by Nicole Schmelzer on 25.04.15.
//

#ifndef SIMPLEOPENGLVIEWER_CAMERA_H
#define SIMPLEOPENGLVIEWER_CAMERA_H

#include <QtOpenGL>

class Camera {
    public:
        Camera(int width, int height, const QVector3D &eye, const QVector3D &center, const QVector3D &up);

        QVector3D eye;
        QVector3D center;
        QVector3D up;
        QMatrix4x4 projection;
        QMatrix4x4 lookAtMat;

        void updatePerspective(float fovy);
    private:
        float fovy;
        float aspect;
};


#endif //SIMPLEOPENGLVIEWER_CAMERA_H
