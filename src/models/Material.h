/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 29.04.15
 */

#ifndef SIMPLEOPENGLVIEWER_MATERIAL_H
#define SIMPLEOPENGLVIEWER_MATERIAL_H

#include <QtOpenGL>
using namespace std;

class Material {
public:
    Material(const QString &name, const QVector4D &ambient, const QVector4D &diffuse, const QVector4D &specular, float shininess);
    QString name;
    QVector4D ambient;
    QVector4D diffuse;
    QVector4D specular;
    float shininess;
};


#endif //SIMPLEOPENGLVIEWER_MATERIAL_H
