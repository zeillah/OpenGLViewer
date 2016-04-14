/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 13.04.2016
 */

#include <cmath>
#include "Model.h"

using namespace std;

Model::Model(Mesh &mesh) : IGeometry()
        , vertexPositionBuffer(QOpenGLBuffer::VertexBuffer)
        , vertexColorBuffer(QOpenGLBuffer::VertexBuffer)
        , indexBuffer(QOpenGLBuffer::IndexBuffer)
        , edgeColorBuffer(QOpenGLBuffer::VertexBuffer)
        , material(shared_ptr<Material> (new Material("Zinn",
                            QVector4D(0.11,0.06,0.11, 1.0),
                            QVector4D(0.43, 0.47, 0.54, 1.0),
                            QVector4D(0.33, 0.33, 0.52, 1.0),
                            9.8)))
{
    this->mesh = mesh;
    setupGeometry();
    calculateCentroid();
}

Model::~Model() { }

void Model::setMaterial(shared_ptr<Material> material)
{
    this->material = material;
}

void Model::setupGeometry()
{
    clear();

    offsets.push_back(0);
    offsets.push_back((GLuint)mesh.n_faces() * 3);

    vertexColors = MeshManipulation::paint(mesh);

    // - draw object
    int index = 0;
    Mesh::FaceIter fIt,fBegin;
    fBegin = mesh.faces_begin();

    // - go through faces
    for( fIt = fBegin ; fIt != mesh.faces_end() ; ++fIt)
    {
        // - go through vertices of face
        Mesh::FaceVertexIter fvIt;
        for (fvIt=mesh.fv_iter( *fIt ); fvIt.is_valid(); ++fvIt) {
            Mesh::Point vertex      = mesh.point(*fvIt);
            OpenMesh::Vec3f normal  = mesh.normal(*fvIt);

            // - add vertex, normal and index to lists
            vertices.push_back(QVector3D(vertex[0], vertex[1], vertex[2]));
            normals.push_back(QVector3D(normal[0], normal[1], normal[2]));
            indices.push_back(index);
            ++index;
        }
    }
}

void Model::calculateCentroid() {

    centroid = QVector3D(0.0f, 0.0f, 0.0f);
	float inf = numeric_limits<float>::infinity();
    QVector3D lbn = QVector3D(inf, inf, inf);
    QVector3D rtf = QVector3D(-inf, -inf, -inf);

	Mesh::VertexIter vIt,vBegin,vEnd;
	vBegin = mesh.vertices_begin(); vEnd = mesh.vertices_end();
	for( vIt = vBegin ; vIt != vEnd; ++vIt ) {
		Mesh::Point vertex = mesh.point( *vIt );
		QVector3D p = QVector3D(vertex[0], vertex[1], vertex[2]);
		centroid += p;
		if (p[0] < lbn[0]) lbn[0] = p[0];
		if (p[1] < lbn[1]) lbn[1] = p[1];
		if (p[2] < lbn[2]) lbn[2] = p[2];
		if (p[0] > rtf[0]) rtf[0] = p[0];
		if (p[1] > rtf[1]) rtf[1] = p[1];
		if (p[2] > rtf[2]) rtf[2] = p[2];
	}

	centroid = centroid / (float)mesh.n_vertices();

	QVector3D bbox = (rtf - lbn);
	float s = max(max(abs(bbox[0]), abs(bbox[1])), abs(bbox[2]));
	scaling = 1.0f/s;
}

void Model::clear() {

	vertices.clear();
	normals.clear();
	indices.clear();
	offsets.clear();
}

void Model::smooth(int iterations)
{
    mesh = MeshManipulation::smooth(mesh, iterations);

    setupGeometry();
    rebindBuffers();
}

void Model::decimate(float percent)
{
    int numFaces = (int)(mesh.n_faces() * percent/100);
    mesh = MeshManipulation::collapse(mesh, numFaces);

    setupGeometry();
    rebindBuffers();
}

void Model::subdivide(const QString &method, int numSubdivisions)
{
    mesh = MeshManipulation::subdivision(mesh, numSubdivisions, method);

    setupGeometry();
    rebindBuffers();
}

//############### IGeometry #####################

void Model::initBuffers()
{
    vertexPositionBuffer.create();
    vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);

    vertexColorBuffer.create();
    vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);

    indexBuffer.create();
    indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);

    edgeColorBuffer.create();
    edgeColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
}

void Model::bindBuffers() {

	vertexPositionBuffer.bind();
	vertexPositionBuffer.allocate(vertices.data(), vertices.size() * sizeof(QVector3D));

	vertexColorBuffer.bind();
	vertexColorBuffer.allocate(normals.data(), normals.size() * sizeof(QVector3D));

	indexBuffer.bind();
	indexBuffer.allocate(indices.data(), indices.size() * sizeof(int));

    edgeColorBuffer.bind();
    edgeColorBuffer.allocate(vertexColors.data(), vertexColors.size() * sizeof(QVector3D));
}

void Model::draw(QOpenGLShaderProgram *program)
{
	vertexPositionBuffer.bind();
	program->enableAttributeArray("aPosition");
	program->setAttributeBuffer("aPosition", GL_FLOAT, 0, 3, sizeof(QVector3D));

	vertexColorBuffer.bind();
	program->enableAttributeArray("aNormal");
	program->setAttributeBuffer("aNormal", GL_FLOAT, 0, 3, sizeof(QVector3D));

	indexBuffer.bind();

	for (uint i = 0; i < offsets.size() - 1; i++) {
		GLuint size = offsets.at(i + 1) - offsets.at(i);
		GLuint offset = offsets.at(i);

        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, (GLvoid*)(offset*sizeof(GLuint)));
	}

    edgeColorBuffer.bind();
    program->enableAttributeArray("vertColor");
    program->setAttributeBuffer("vertColor", GL_FLOAT, 0, 3, sizeof(QVector3D));
}