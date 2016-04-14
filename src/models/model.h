/**
 *  \author    : Nicole Schmelzer
 *  \version   : 2.0
 *  \date      : 13.04.16
 */

#ifndef MODEL_H
#define MODEL_H

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <QVector3D>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>
#include <iostream>
#include <limits>

#include "IGeometry.h"
#include "Material.h"
#include "src/transformations/MeshManipulation.h"

/**
 * Class representing the model geometry created from an obj file.
 */

typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;

class Model : public IGeometry {
public:
    Model(Mesh &mesh);

    virtual ~Model();

    float getScaling() { return scaling; };

    QVector3D getCentroid() { return centroid; };

    shared_ptr<Material> getMaterial() { return material; };

    std::vector<QVector3D> getEdgeVertices() { return MeshManipulation::paint(mesh); };


    virtual void draw(QOpenGLShaderProgram *program);

    void smooth(int iterations);

    void decimate(float percent);

    void subdivide(const QString &method, int numSubdivisions);

    void setMaterial(shared_ptr<Material> material);

private:
    QOpenGLBuffer vertexPositionBuffer;
    QOpenGLBuffer vertexColorBuffer;
    QOpenGLBuffer indexBuffer;
    QOpenGLBuffer edgeColorBuffer;

    std::vector<QVector3D> vertices;
    std::vector<QVector3D> normals;
    std::vector<GLuint> indices;
    std::vector<GLuint> offsets;
    QVector3D centroid;
    float scaling;


    Mesh mesh;
    shared_ptr<Material> material;
    std::vector<QVector3D> vertexColors;

    virtual void initBuffers();
    virtual void bindBuffers();

    void clear();
    void calculateCentroid();
    void setupGeometry();
    void rebindBuffers() { bindBuffers(); };
};

#endif /* MODEL_H */
