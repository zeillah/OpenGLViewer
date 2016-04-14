#include "dual_quaternion.h"
#include <iostream>
using namespace cvmr;

DualQuaternion::DualQuaternion() : real(QQuaternion(1, 0, 0, 0)), dual(QQuaternion(0, 0, 0, 0))
{}

DualQuaternion::DualQuaternion(const DualQuaternion& other) : real(other.real), dual(other.dual)
{}

DualQuaternion::DualQuaternion(const QQuaternion& r, const QQuaternion& d) : real(r), dual(d)
{}

DualQuaternion::DualQuaternion(const QQuaternion& r, const QVector3D tVec)
{
    init(r, tVec);
}

void DualQuaternion::init(const QQuaternion& r, const QVector3D tVec)
{
    real = QQuaternion(r).normalized();
    dual = (QQuaternion(0, tVec) * real) * 0.5f;
}

QQuaternion DualQuaternion::getRotation()
{
    return real;
}

QVector3D DualQuaternion::getTranslation()
{
    QQuaternion q = (dual * real.conjugate()) * 2.0f;
    return q.vector();
}

bool DualQuaternion::operator==(const DualQuaternion& other) const
{
    return ((*this).real == other.real && (*this).dual == other.dual);
}

bool DualQuaternion::operator!=(const DualQuaternion& other) const
{
    return !(*this == other);
}

DualQuaternion DualQuaternion::operator+(const DualQuaternion& other) const
{
    return DualQuaternion(real+other.real, dual+other.dual);
}

DualQuaternion& DualQuaternion::operator+=(const DualQuaternion& other)
{
    return (*this = (*this) + other);
}

DualQuaternion DualQuaternion::operator-(const DualQuaternion& other) const
{
    return DualQuaternion(real-other.real, dual-other.dual);
}

DualQuaternion& DualQuaternion::operator-=(const DualQuaternion& other)
{
    return (*this = (*this) - other);
}

DualQuaternion DualQuaternion::operator*(double scale) const
{
    return DualQuaternion(real*scale, dual*scale);
}

DualQuaternion& DualQuaternion::operator*=(double scale)
{
    return (*this = (*this) * scale);
}

DualQuaternion DualQuaternion::operator/(double scale) const
{
    return DualQuaternion(real/scale, dual/scale);
}

DualQuaternion& DualQuaternion::operator/=(double scale)
{
    return (*this = (*this) / scale);
}

DualQuaternion DualQuaternion::operator*(const DualQuaternion& other)
{
    return DualQuaternion(real*other.real, real*other.dual + dual*other.real);
}

DualQuaternion& DualQuaternion::operator*=(DualQuaternion& other)
{
    return (*this = (*this) * other);
}

DualQuaternion DualQuaternion::conj() const
{
    return DualQuaternion(real.conjugate(), dual.conjugate());
}

DualQuaternion& DualQuaternion::normalize()
{
    double magnitude = (*this).magnitude();

    if (magnitude == 0)
    {
        return *this;
    }

    return (*this = (*this) / magnitude);
}

double DualQuaternion::dot(DualQuaternion& other) const
{
    return real.scalar() * other.real.scalar()
           + real.vector()[0] * other.real.vector()[0]
           + real.vector()[1] * other.real.vector()[1]
           + real.vector()[2] * other.real.vector()[2];
}

double DualQuaternion::magnitude() const
{
    DualQuaternion q = DualQuaternion(*this);
    return sqrt(q.dot(q));
}

DualQuaternion DualQuaternion::sclerp3(const DualQuaternion& dqa, const DualQuaternion& dqb, double t)
{
    if (t <= 0.0)
        return dqa;

    if (t >= 1.0)
        return dqb;

    DualQuaternion dq0 = DualQuaternion(dqa);
    DualQuaternion dq1 = DualQuaternion(dqb);

    // Shortest path
    double dot = dq0.dot(dq1);
    if(dot < 0) {
        dq1 = dq1 * -1.0f;
    }
    DualQuaternion res = (dq0 * (1-t) + dq1 * t);
    res /= res.magnitude();
    return res;
}