//
// Created by Nicole Schmelzer on 29.04.15.
//

#include "MaterialBox.h"
MaterialBox::MaterialBox()
{

    materials.push_back(shared_ptr<Material>(new Material(QString("Chrom"),
                                 QVector4D(0.25,0.25,0.25, 1.0),
                                 QVector4D(0.40, 0.40, 0.40, 1.0),
                                 QVector4D(0.77, 0.77, 0.77, 1.0),
                                 76.8)));

    materials.push_back(shared_ptr<Material>(new Material(QString("Gold"),
                                 QVector4D(0.25, 0.22, 0.06, 1.0),
                                 QVector4D(0.35, 0.31, 0.09, 1.0),
                                 QVector4D(0.80, 0.72, 0.21, 1.0),
                                 83.2)));

    materials.push_back(shared_ptr<Material>(new Material(QString("Jade"),
                                 QVector4D(0.14,0.22,0.16, 0.9),
                                 QVector4D(0.54, 0.89, 0.63, 0.9),
                                 QVector4D(0.32, 0.32, 0.32, 0.9),
                                 12.8)));

    materials.push_back(shared_ptr<Material>(new Material(QString("Obsidian"),
                        QVector4D(0.05,0.05,0.07, 0.8),
                        QVector4D(0.18, 0.17, 0.23, 0.8),
                        QVector4D(0.33, 0.33, 0.35, 0.8),
                        38.4)));

    materials.push_back(shared_ptr<Material>(new Material(QString("Rubin"),
                                 QVector4D(0.17,0.01,0.01, 0.5),
                                 QVector4D(0.61, 0.04, 0.04, 0.5),
                                 QVector4D(0.73, 0.63, 0.63, 0.5),
                                 76.8)));

    materials.push_back(shared_ptr<Material>(new Material(QString("Zinn"),
                             QVector4D(0.11,0.06,0.11, 1.0),
                             QVector4D(0.43, 0.47, 0.54, 1.0),
                             QVector4D(0.33, 0.33, 0.52, 1.0),
                             9.8)));
}

shared_ptr<Material> MaterialBox::getMaterial(const QString &name)
{
    for(int i = 0; i < materials.size(); i++) {
        if(materials[i]->name == name)
            return materials[i];
    }
    return materials[0];
}