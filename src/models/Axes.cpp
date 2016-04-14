/**
 *  \author    : Marc Lieser, Henning Tjaden
 *  \version   : 1.0
 *  \date      : 09.10.2014
 *  \copyright : Copyright (c)
 *               Computer Vision & Mixed Reality Group,
 *               Hochschule RheinMain University of Applied Sciences
 */

#include "Axes.h"

using namespace std;

Axes::Axes() : IGeometry() {
    float l = 1.0f;

     static const float vp[] = {
            0, 0, 0,
            l, 0, 0,
            0, 0, 0,
            0, l, 0,
            0, 0, 0,
            0, 0, l
    };

    static const float vc[] = {
            1, 0, 0,
            1, 0, 0,
            0, 1, 0,
            0, 1, 0,
            0, 0, 1,
            0, 0, 1
    };

    vertexPositions = vp;
    vertexColors = vc;
}

Axes::~Axes() {
}

void Axes::initBuffers()
{
	vertexPositionBuffer.create();
	vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);

	vertexColorBuffer.create();
	vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);

	indexBuffer.create();
	indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
}
void Axes::bindBuffers()
{
    vertexPositionBuffer.bind();
    vertexPositionBuffer.allocate(vertexPositions, 18 * sizeof(float));

    vertexColorBuffer.bind();
    vertexColorBuffer.allocate(vertexColors, 18 * sizeof(float));

    ushort indices[] = {0,1,2,3,4,5,6};

    indexBuffer.bind();
    indexBuffer.allocate(indices, 6*sizeof(ushort));
}

void Axes::draw(QOpenGLShaderProgram *program) {

	vertexPositionBuffer.bind();
	program->enableAttributeArray("aPosition");
	program->setAttributeBuffer("aPosition", GL_FLOAT, 0, 3);

	vertexColorBuffer.bind();
	program->enableAttributeArray("aColor");
	program->setAttributeBuffer("aColor", GL_FLOAT, 0, 3);

    indexBuffer.bind();
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, 0);
}
