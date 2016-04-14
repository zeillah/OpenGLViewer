/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 29.04.15
 */

#include "Material.h"
Material::Material(const QString &name, const QVector4D &ambient, const QVector4D &diffuse, const QVector4D &specular, float shininess)
{
    this->name = name;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
}