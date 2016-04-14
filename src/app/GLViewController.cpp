//
// Created by Nicole Schmelzer on 13.04.16.
//

#include "GLViewController.h"
using namespace std;

GLViewController::GLViewController(int _width, int _height)
{
    width = _width;
    height = _height;
    animation = new Animation(2000);
    arcball = new Arcball(width, height);
    doRotation = false;
    doTranslation = false;
    doScaling = false;

    connect(animation, SIGNAL(rotationChanged(QQuaternion)), this, SLOT(onRotationChanged(QQuaternion)));
    connect(animation, SIGNAL(translationChanged(QMatrix4x4)), this, SLOT(onTranslationChanged(QMatrix4x4)));
}

GLViewController::~GLViewController() { }

void GLViewController::mousePressEvent(QMouseEvent *e)
{

    if(e->button() == Qt::LeftButton) {
        doRotation = true;
        // - start arcball
        QVector3D center = QVector3D(lastTranslation.operator()(3,0), lastTranslation.operator()(3,1), lastTranslation.operator()(3,2));
        arcball->startRotation( e->x(), e->y(), center);
    }

    if(e->button() == Qt::RightButton) {
        doTranslation = true;
        startP = QVector3D(1.0f * e->x()/width*2 - 1.0f,
                                    1.0f * e->y()/height*2 - 1.0f,
                                            0);
    }
}

void GLViewController::wheelEvent(QWheelEvent *event)
{
    if(abs(event->delta()) > 2) {
        int numDegrees = event->delta() / 8;

        if (event->orientation() == Qt::Vertical) {
            if(numDegrees > 0) {
                emit scalingChanged(-0.5f);
            } else {
                emit scalingChanged(0.5f);
            }
        }
        event->accept();
    }
}

void GLViewController::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton) {
        arcball->updateRotation( e->x(), e->y() );
        emit rotationChanged(arcball->getCurrentRotation());
    }

    if(e->buttons() == Qt::RightButton) {
        QVector3D point = QVector3D(1.0f * e->x()/width*2 - 1.0f,
                                    1.0f * e->y()/height*2 - 1.0f,
                                    0);
        double x = startP.x() - point.x();
        double y = startP.y() - point.y();

        currentTranslation = QMatrix4x4(
                1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, 0,
                0, 0, 0, 1
        ) * lastTranslation;
        emit translationChanged(currentTranslation);
    }
}

void GLViewController::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton) {
        doRotation = false;
        arcball->stopRotation();
    }

    if(e->button() == Qt::RightButton) {
        doTranslation = false;
        lastTranslation = currentTranslation;
    }
}

void GLViewController::keyReleaseEvent(QKeyEvent * event)
{
    if( event->key() == Qt::Key_A )
    {
        QQuaternion quat = arcball->getCurrentRotation();
        QVector3D trans = QVector3D(lastTranslation.operator()(0, 3), lastTranslation.operator()(1, 3), lastTranslation.operator()(2,3));
        positionA = cvmr::DualQuaternion(quat, trans);

        emit positionSaved("A");

    }

    if( event->key() == Qt::Key_B )
    {
        QQuaternion quat = arcball->getCurrentRotation();
        QVector3D trans = QVector3D(lastTranslation.operator()(0, 3), lastTranslation.operator()(1, 3), lastTranslation.operator()(2, 3));
        positionB = cvmr::DualQuaternion(quat, trans);

        emit positionSaved("B");
    }

    if( event->key() == Qt::Key_Space )
    {
        animation->setStartPosition(positionA);
        animation->setEndPosition(positionB);
        animation->start();
    }
}


void GLViewController::onRotationChanged(QQuaternion rot)
{
    arcball->setRotation(rot);
    emit rotationChanged(rot);
}

void GLViewController::onTranslationChanged(QMatrix4x4 trans)
{
    lastTranslation = currentTranslation;
    currentTranslation = trans;
    emit translationChanged(currentTranslation);
}