/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 01.05.2015
 */

#ifndef OPENGLVIEWER_LIGHT_H
#define OPENGLVIEWER_LIGHT_H


#include <QtOpenGL>

class Light {
public:
    Light(const QVector3D &position, const QVector4D &color, float ambientCoefficient, float attenuation, const QVector3D &coneDirection, float coneAngle);
    Light(const QVector3D &position, const QVector4D &color, float ambientCoefficient, float attenuation);
    QVector3D position;
    QVector4D color;
    float ambientCoefficient;
    float attenuation;
    float coneAngle;    // new
    QVector3D coneDirection; // new
};


#endif //OPENGLVIEWER_LIGHT_H
