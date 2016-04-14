//
// Created by Nicole Schmelzer on 26.04.15.
//

#ifndef SIMPLEOPENGLVIEWER_ARCBALL_H
#define SIMPLEOPENGLVIEWER_ARCBALL_H

#include <QtOpenGL>
class Arcball {
    public:
        Arcball(float width, float height);

        float angle;
        QVector3D axis;

        float w;
        float h;

        void startRotation(int x, int y, const QVector3D &center);
        QQuaternion updateRotation(int x, int y);
        void stopRotation();
        QQuaternion getCurrentRotation();
        void setRotation(QQuaternion rot);

    private:
        float arcballRadius;
        QVector3D center;
        QVector3D startP;
        QVector3D moveP;

        QQuaternion currentRotation;
        QQuaternion lastRotation;

        QVector3D projectOnSphere(int x, int y);
};


#endif //SIMPLEOPENGLVIEWER_ARCBALL_H
