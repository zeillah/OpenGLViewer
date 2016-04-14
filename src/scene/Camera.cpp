//
// Created by Nicole Schmelzer on 25.04.15.
//

#include "Camera.h"

Camera::Camera(int width, int height, const QVector3D &eye, const QVector3D &center, const QVector3D &up)
{
    this->eye = eye;
    this->center = center;
    this->up = up;
    this->fovy = 45.0f;

    this->aspect = (float) width / height;
    // - uses angle degree
    projection.perspective(this->fovy, this->aspect, 0.1, 2000.0);

    // - uses bogenmass
    // projection = perspectiveMatrix(45.0, aspect, 0.1, 2000.0);
    lookAtMat.lookAt( eye, center, up );
}

void Camera::updatePerspective(float fovy)
{
    if(fovy > 0 && this->fovy < 180) {
        this->fovy += fovy;
    }

    if(fovy < 0 && this->fovy > 0) {
        this->fovy += fovy;
    }

    projection = QMatrix4x4();
    projection.perspective(this->fovy, this->aspect, 0.1, 2000.0);
}