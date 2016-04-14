//
// Created by Nicole Schmelzer on 04.05.15.
//

#include "Animation.h"
#include <iostream>

Animation::Animation(int animationLength)
{
    this->steps = animationLength/ 60.0f; // 60 frames
    this->increaseValue = 1.0f/this->steps;
    this->t = 0.0;

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), SLOT(animate()));

}

Animation::Animation(int animationLength, cvmr::DualQuaternion qStart, cvmr::DualQuaternion qEnd)
{
    this->qStart = qStart;
    this->qEnd = qEnd;
    this->steps = animationLength/ 60.0f; // 60 frames
    this->increaseValue = 1.0f/this->steps;
    this->t = 0.0;

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), SLOT(animate()));

}

void Animation::setStartPosition(cvmr::DualQuaternion qStart)
{
    this->qStart = qStart;
}
void Animation::setEndPosition(cvmr::DualQuaternion qEnd)
{
    this->qEnd = qEnd;
}

void Animation::start()
{
    this->t = 1.0;
    mTimer->start(steps);
}

void Animation::animate()
{
    float delta = increaseValue;
    if(t < 0.0 - delta) {
        mTimer->stop();
    } else {
        cvmr::DualQuaternion a = cvmr::DualQuaternion::sclerp3(this->qStart, this->qEnd, t);

        QQuaternion rotation = a.getRotation();
        QVector3D tr = a.getTranslation();

        QMatrix4x4 translation = QMatrix4x4(
                1, 0, 0, (float) tr[0],
                0, 1, 0, (float) tr[1],
                0, 0, 1, (float) tr[2],
                0, 0, 0, 1
        );

        t = t - increaseValue;

        emit rotationChanged(rotation);
        emit translationChanged(translation);
    }
}