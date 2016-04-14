/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 29.04.15
 */

#ifndef SIMPLEOPENGLVIEWER_MATERIALBOX_H
#define SIMPLEOPENGLVIEWER_MATERIALBOX_H
#include "Material.h"
using namespace std;

class MaterialBox {
public:
    MaterialBox();
    //vector<Material> materials;
    vector<shared_ptr<Material> > materials;
    shared_ptr<Material> getMaterial(const QString &name);
};


#endif //SIMPLEOPENGLVIEWER_MATERIALBOX_H
