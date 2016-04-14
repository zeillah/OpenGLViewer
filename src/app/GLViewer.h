/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 13.04.16
 */

#ifndef OPENGLVIEWER_GL_VIEWER_H
#define OPENGLVIEWER_GL_VIEWER_H
#include <QtOpenGL>
#include "src/scene/Scene.h"
#include "GLViewController.h"

class GLViewer : public QGLWidget
{
    Q_OBJECT        // must include this if you use Qt signals/slots

public:
    GLViewer(const QGLFormat& format, const QString &modelPath, const QString &shaderFolder, int height, int width, QWidget *parent);

    Scene* getScene() { return scene; }

    public slots:
        void onPosition(const QString &);
        void onScalingChanged(float);
        void onRotationChanged(const QQuaternion &);
        void onTranslationChanged(const QMatrix4x4 &);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

private:
    GLViewController *controller;
    Scene *scene;
    QString shaderFolder;
    QOpenGLShaderProgram *vertexcolorProgram;
    QOpenGLShaderProgram *modelProgram;

    bool initShaderProgram(QOpenGLShaderProgram *program, const QString &shaderName);
};


#endif //OPENGLVIEWER_GL_VIEWER_H
