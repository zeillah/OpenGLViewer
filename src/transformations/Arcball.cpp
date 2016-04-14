/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 26.04.15
 */

#include "Arcball.h"

#include <iostream>
using namespace std;

Arcball::Arcball(float width, float height)
{
    w = width;
    h = height;
    arcballRadius = 1;
}

QVector3D Arcball::projectOnSphere(int x, int y)
{
    QVector3D touchPoint = QVector3D(1.0f * x/w*2 - 1.0f,
                                     1.0f * y/h*2 - 1.0f,
                                     0);

    float pSqared = touchPoint.x() * touchPoint.x() + touchPoint.y() * touchPoint.y();
    if (pSqared <= arcballRadius*arcballRadius) {
        touchPoint[2] = sqrtf(arcballRadius*arcballRadius - pSqared);  // pythagore
    } else {
        touchPoint = touchPoint.normalized();  // nearest point
    }
    return touchPoint;
}

void Arcball::startRotation(int x, int y, const QVector3D &center)
{
    this->center = center;
    startP = projectOnSphere(x, y);
}

QQuaternion Arcball::updateRotation(int x, int y)
{
    moveP = projectOnSphere(x, y);
    angle = qRadiansToDegrees( acosf(min(1.0f, QVector3D::dotProduct(startP , moveP))) );
    axis = QVector3D::crossProduct(startP, moveP);
    axis.normalize();
    currentRotation = QQuaternion::fromAxisAndAngle(axis, angle) * lastRotation;
    currentRotation.normalize();
    return currentRotation;
}

void Arcball::stopRotation()
{
    lastRotation = currentRotation;
}

QQuaternion Arcball::getCurrentRotation()
{
    return currentRotation.normalized();
}

void Arcball::setRotation(QQuaternion rotation)
{
    lastRotation = currentRotation;
    currentRotation = rotation;
}