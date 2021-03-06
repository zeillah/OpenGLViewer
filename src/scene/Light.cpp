/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 01.05.2015
 */

#include "Light.h"

Light::Light(const QVector3D &position, const QVector4D &color, float ambientCoefficient, float attenuation)
{
    this->position = position;
    this->color = color;
    this->ambientCoefficient = ambientCoefficient;
    this->attenuation = attenuation;
}

Light::Light(const QVector3D &position, const QVector4D &color, float ambientCoefficient, float attenuation, const QVector3D &coneDirection, float coneAngle)
{
    /*this->position = position;
    this->color = color;
    this->ambientCoefficient = ambientCoefficient;
    this->attenuation = attenuation;*/
    Light(position, color, ambientCoefficient, attenuation);
    this->coneDirection = coneDirection;
    this->coneAngle = coneAngle;
}
