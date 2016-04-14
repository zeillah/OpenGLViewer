//
// Created by Nicole Schmelzer on 13.04.16.
//

#include "GLViewer.h"

using namespace std;

GLViewer::GLViewer(const QGLFormat& format, const QString &modelPath, const QString &shaderFolder,
                   int height, int width, QWidget *parent) : QGLWidget(format, parent)
    , shaderFolder(shaderFolder)
    , vertexcolorProgram(new QOpenGLShaderProgram)
    , modelProgram(new QOpenGLShaderProgram)
{
    this->setMinimumSize(QSize(width, height));
    this->setFocusPolicy(Qt::StrongFocus);

    scene = new Scene(width, height, modelPath, vertexcolorProgram, modelProgram);
    controller = new GLViewController(width, height);

    connect(controller, SIGNAL(positionSaved(const QString &)), this, SLOT(onPosition(const QString &)));
    connect(controller, SIGNAL(scalingChanged(float)), this, SLOT(onScalingChanged(float)));
    connect(controller, SIGNAL(rotationChanged(const QQuaternion &)), this, SLOT(onRotationChanged(const QQuaternion &)));
    connect(controller, SIGNAL(translationChanged(const QMatrix4x4 &)), this, SLOT(onTranslationChanged(const QMatrix4x4 &)));
}

void GLViewer::initializeGL()
{
    // Set up the rendering context, define display lists etc.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    // from https://qt-project.org/wiki/How_to_use_OpenGL_Core_Profile_with_Qt
    // On some setups (Windows 7, NVidia 9800 GT using drivers 285.62), it is required to bind a VAO before setting up the attributes.
    // This behavior is part of the OpenGL 3.3 core profile. This is done by calling:
    uint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // initialize shaders
    initShaderProgram(vertexcolorProgram, "vertexcolor");
    initShaderProgram(modelProgram, "model_phong");

    scene->init();
}

void GLViewer::resizeGL(int w, int h) {
    // - setup viewport
    float dpr = devicePixelRatio();
    glViewport(0, 0, int(w * dpr), int(h * dpr));
}

void GLViewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->render();
}

bool GLViewer::initShaderProgram(QOpenGLShaderProgram *program, const QString &shaderName) {

    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, shaderFolder + shaderName + QString("_vertex_shader.glsl"))) {
        cout << "error adding vertex shader from source file" << endl;
        return false;
    }


    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, shaderFolder + shaderName + QString("_fragment_shader.glsl"))) {
        cout << "error adding fragment shader from source file" << endl;
        return false;
    }

    if (!program->link()) {
        cout << "error linking shaders" << endl;
        return false;
    }
    return true;
}

void GLViewer::onScalingChanged(float scaling)
{
    scene->updateScaling(scaling);

    updateGL();
}

void GLViewer::onRotationChanged(const QQuaternion &quat)
{
    QMatrix4x4 rotation;
    rotation.rotate(quat);
    scene->updateRotation(rotation);

    updateGL();
}

void GLViewer::onTranslationChanged(const QMatrix4x4 &translation)
{
    scene->updateTranslation(translation);

    updateGL();
}

void GLViewer::mousePressEvent(QMouseEvent *e)
{
    controller->mousePressEvent(e);
}

void GLViewer::wheelEvent(QWheelEvent *e)
{
    controller->wheelEvent(e);
}

void GLViewer::mouseMoveEvent(QMouseEvent *e)
{
    controller->mouseMoveEvent(e);
}

void GLViewer::mouseReleaseEvent(QMouseEvent *e)
{
    controller->mouseReleaseEvent(e);
}

void GLViewer::keyReleaseEvent(QKeyEvent *e)
{
    controller->keyReleaseEvent(e);
}

void GLViewer::onPosition(const QString &pos)
{
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Info", "Position " + pos +" saved.");

    QTimer *msgBoxCloseTimer = new QTimer(this);
    msgBoxCloseTimer->setInterval(700);
    msgBoxCloseTimer->setSingleShot(true);
    connect(msgBoxCloseTimer, SIGNAL(timeout()), msgBox, SLOT(reject())); // or accept()
    msgBoxCloseTimer->start();

    msgBox->exec();
}