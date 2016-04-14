/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 13.04.16
 */

#ifndef OPENGLVIEWER_IGEOMETRY_H
#define OPENGLVIEWER_IGEOMETRY_H

class IGeometry{
public:
    virtual ~IGeometry() {}
    void init() {
        initBuffers();
        bindBuffers();
    };
    virtual void draw(QOpenGLShaderProgram *program) = 0;

private:
    virtual void initBuffers() = 0;
    virtual void bindBuffers() = 0;
};

#endif //OPENGLVIEWER_IGEOMETRY_H
