/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 13.04.16
 */

#ifndef AXES_H
#define AXES_H
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "IGeometry.h"

/**
 * Coordinate system axes geometry.
 */
class Axes: public IGeometry {

public:

	Axes();
	virtual ~Axes();

	void draw(QOpenGLShaderProgram *program);

private:
	QOpenGLBuffer vertexPositionBuffer;
	QOpenGLBuffer vertexColorBuffer;
	QOpenGLBuffer indexBuffer;

    const float *vertexPositions;
    const float *vertexColors;

	virtual void initBuffers();
	virtual void bindBuffers();
};

#endif /* AXES_H */
