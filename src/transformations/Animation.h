//
// Created by Nicole Schmelzer on 04.05.15.
//

#ifndef OPENGLVIEWER_ANIMATION_H
#define OPENGLVIEWER_ANIMATION_H

#include <QTimer>

#include "src/dualquaternion/dual_quaternion.h"

class Animation : public QObject {
    Q_OBJECT
    public:
        Animation(int animationLength);
        Animation(int animationLength, cvmr::DualQuaternion qStart, cvmr::DualQuaternion qEnd);
        void start();
        void setStartPosition(cvmr::DualQuaternion qStart);
        void setEndPosition(cvmr::DualQuaternion qEnd);
    signals:
        void rotationChanged(QQuaternion);
        void translationChanged(QMatrix4x4);

    private slots:
        void animate();


    private:
        float steps;
        float increaseValue;
        float t;

        cvmr::DualQuaternion qStart;
        cvmr::DualQuaternion qEnd;
        QTimer* mTimer;
};


#endif //OPENGLVIEWER_ANIMATION_H
