/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 25.04.2015
 */

#include "Camera.h"

Camera::Camera(int width, int height, const QVector3D &eye, const QVector3D &center, const QVector3D &up)
{
    this->eye = eye;
    this->center = center;
    this->up = up;
    this->fovy = 45.0f;

    this->aspect = (float) width / height;

    projection.perspective(this->fovy, this->aspect, 0.1, 2000.0);
    lookAtMat.lookAt( eye, center, up );
}

void Camera::updatePerspective(float fovy)
{
    this->fovy += fovy;
    projection = QMatrix4x4();
    projection.perspective(this->fovy, this->aspect, 0.1, 2000.0);
}