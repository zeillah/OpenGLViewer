/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 13.04.2016
 */

#ifndef OPENGLVIEWER_GLVIEWCONTROLLER_H
#define OPENGLVIEWER_GLVIEWCONTROLLER_H

#include <QMouseEvent>
#include "src/transformations/Animation.h"
#include "src/transformations/Arcball.h"

class GLViewController : public QObject {
    Q_OBJECT        // must include this if you use Qt signals/slots
public:
    GLViewController(int width, int height);
    ~GLViewController();

    void mousePressEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyReleaseEvent(QKeyEvent * event);

    public slots:
        void onRotationChanged(QQuaternion);
        void onTranslationChanged(QMatrix4x4);
    signals:
        void positionSaved(const QString &);
        void scalingChanged(float);
        void rotationChanged(const QQuaternion &);
        void translationChanged(const QMatrix4x4 &);

private:
    int width;
    int height;

    Animation *animation;
    Arcball *arcball;
    bool doRotation;
    bool doTranslation;
    bool doScaling;

    // - Translation
    QVector3D startP;

    QMatrix4x4 currentTranslation;
    QMatrix4x4 lastTranslation;

    // - Animation
    cvmr::DualQuaternion positionA;
	cvmr::DualQuaternion positionB;
	float t;
};


#endif //OPENGLVIEWER_GLVIEWCONTROLLER_H
