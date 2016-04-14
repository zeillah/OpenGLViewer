/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 13.06.15
 */

#ifndef OPENGLVIEWER_OBJ_READER_H
#define OPENGLVIEWER_OBJ_READER_H

#include <QString>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include <QVector3D>
#include <QVector2D>

// -------------------- OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

struct MyTraits : public OpenMesh::DefaultTraits {
    VertexAttributes(OpenMesh::Attributes::Normal |
                     OpenMesh::Attributes::Color);
    FaceAttributes(OpenMesh::Attributes::Normal);
};

typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;

class ObjReader {
public:
    static Mesh initGeometryFromObjFile(QString _filename);

};

#endif //OPENGLVIEWER_OBJ_READER_H
