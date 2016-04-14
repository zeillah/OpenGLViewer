/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 16.06.15
 */

#ifndef OPENGLVIEWER_TRANSFORMATION_H
#define OPENGLVIEWER_TRANSFORMATION_H

#include <iostream>
#include <QString>
#include <map>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Smoother/JacobiLaplaceSmootherT.hh>
#include <OpenMesh/Tools/Decimater/DecimaterT.hh>
#include <OpenMesh/Tools/Decimater/ModQuadricT.hh>
#include <OpenMesh/Core/Geometry/QuadricT.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/LoopT.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/Sqrt3T.hh>

typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;

class MeshManipulation {
public:
    static std::vector<QVector3D> paint(Mesh &mesh);
    static Mesh smooth(Mesh &mesh, int iterations);
    static Mesh collapse(Mesh &mesh, int numFaces);
    static Mesh subdivision(Mesh &mesh, int numSubdivisions, const QString &method);

private:
    static Mesh smoothOpenMesh(Mesh &mesh, int iterations);
    static Mesh collapseOpenMesh(Mesh &mesh, int numFaces);
    static Mesh loopSubdivision(Mesh &mesh, int numSubdivisions);
    static Mesh sqrt3Subdivision(Mesh &mesh, int numSubdivisions);

    static Mesh smoothValence(Mesh &mesh, int iterations);
    static Mesh smoothLength(Mesh &mesh, int iterations);
};


#endif //OPENGLVIEWER_TRANSFORMATION_H
