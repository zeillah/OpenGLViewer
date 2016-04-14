/******************************************************
 *
 *   #, #,         CCCCCC  VV    VV MM      MM RRRRRRR
 *  %  %(  #%%#   CC    CC VV    VV MMM    MMM RR    RR
 *  %    %## #    CC        V    V  MM M  M MM RR    RR
 *   ,%      %    CC        VV  VV  MM  MM  MM RRRRRR
 *   (%      %,   CC    CC   VVVV   MM      MM RR   RR
 *     #%    %*    CCCCCC     VV    MM      MM RR    RR
 *    .%    %/
 *       (%.      Computer Vision & Mixed Reality Group
 *
 *****************************************************/
/** @copyright    Hochschule RheinMain,
 *                University of Applied Sciences
 *     @author    Thomas Gietzen
 *    @version    0.9
 *       @date    15.01.2015
 *****************************************************/

#ifndef DUAL_QUATERNION_H
#define DUAL_QUATERNION_H

#include <QtOpenGL>
#include <string.h>

namespace cvmr
{
    /**
     * @brief Class representing unit dual quaternions.
     */
    class DualQuaternion
    {

    public:
        /// Default dib tolerance
        static const double DEFAULT_DIB_TOLERANCE = 1e-6;

        /// Default dib maximum iterations
        static const int DEFAULT_DIB_MAX_ITERS = 3;

        /**
         * @brief Default constructor.
         */
        DualQuaternion();

        /**
         * @brief Copy constructor.
         * @param other - dual quaternion
         */
        DualQuaternion(const DualQuaternion& other);

        /**
         * @brief Constructor with given quaternion components.
         * @param r - real
         * @param d - dual
         */
        DualQuaternion(const QQuaternion& r, const QQuaternion& d);

        /**
         * @brief Constructor with quaternion and translation vector.
         * @param r - real
         * @param tVec - translation vector
         */
        DualQuaternion(const QQuaternion& r, const QVector3D tVec);

        /**
         * @brief Get rotation quaternion.
         * @return rotation quaternion
         */
        QQuaternion getRotation();

        /**
         * @brief Get translation vector.
         * @return translation vector
         */
        QVector3D getTranslation();

        /**
         * @brief Assignment constructor.
         * @param other - dual quaternion
         */
        inline DualQuaternion& operator=(const DualQuaternion& other);

        /**
         * @brief Check if this dual quaternion is equal to another.
         * @param other - dual quaternion
         */
        bool operator==(const DualQuaternion& other) const;

        /**
         * @brief Check if this dual quaternion is not equal to another.
         * @param other - dual quaternion
         */
        bool operator!=(const DualQuaternion& other) const;

        /**
         * @brief Add dual quaternions.
         * @param other - dual quaternion
         * @return new dual quaternion
         */
        DualQuaternion operator+(const DualQuaternion& other) const;

        /**
         * @brief Add other to current dual quaternion.
         * @param other - dual quaternion
         */
        DualQuaternion& operator+=(const DualQuaternion& other);

        /**
         * @brief Sub dual quaternions.
         * @param other - dual quaternion
         * @return new dual quaternion
         */
        DualQuaternion operator-(const DualQuaternion& other) const;

        /**
         * @brief Sub other from current dual quaternion.
         * @param other - dual quaternion
         */
        DualQuaternion& operator-=(const DualQuaternion& other);

        /**
         * @brief Multiply dual quaternion with scale.
         * @param scale
         * @return scaled dual quaternion
         */
        DualQuaternion operator*(double scale) const;

        /**
         * @brief Multiply current dual quaternion with scale.
         * @param scale
         */
        DualQuaternion& operator*=(double scale);

        /**
         * @brief Divide dual quaternion by scale.
         * @param scale
         * @return scaled dual quaternion
         */
        DualQuaternion operator/(double scale) const;

        /**
         * @brief Divide current dual quaternion by scale.
         * @param scale
         */
        DualQuaternion& operator/=(double scale);

        /**
         * @brief Multiply dual quaternions.
         * @param other - dual quaternion
         * @return new dual quaternion
         */
        DualQuaternion operator*(const DualQuaternion& other);

        /**
         * @brief Multiply current with other dual quaternion.
         * @param other - dual quaternion
         */
        DualQuaternion& operator*=(DualQuaternion& other);

        /**
         * @brief Calculate conjugate.
         * @return conjugated dual quaternion
         */
        DualQuaternion conj() const;

        /**
         * @brief Make unit dual quaternion.
         */
        DualQuaternion& normalize();

        /**
         * @brief Make dot product.
         * @param other - dual quaternion
         * @return dot product
         */
        double dot(DualQuaternion& other) const;

        /**
         * @brief Calculate the magnitude of dual quaternion.
         * @return magnitude of dual quaternion
         */
        double magnitude() const;

        static DualQuaternion sclerp3(const DualQuaternion& dqa, const DualQuaternion& dqb, double t);

        /**
         * @brief Print dual quaternion out to stream.
         * @param out - ostream
         * @param q - dual quaternion
         */
        friend std::ostream& operator<<(std::ostream& out, const DualQuaternion& q)
        {
            QVector4D r = q.real.toVector4D();
            QVector4D d = q.dual.toVector4D();

            QString s = "[ (" + QString::number(r[0]) + ", ( " + QString::number(r[1]) + ", " + QString::number(r[2]) + ", " + QString::number(r[3]) + ")," + "(" + QString::number(d[0]) + ",[( " + QString::number(d[1]) + ", " + QString::number(d[2]) + ", " + QString::number(d[3]) + ")]";
            return out << s.toStdString();
        }

    protected:
        /// Real part of dual quaternion
        QQuaternion real;

        /// Dual part of dual quaternion
        QQuaternion dual;

    private:
        /**
         * @brief Initialize helper function for constructor.
         * @param r - rotation quaternion
         * @param tVec - translation vector
         */
        void init(const QQuaternion& r, const QVector3D tVec);
    };

    inline DualQuaternion& DualQuaternion::operator=(const DualQuaternion& other)
    {
        real = other.real;
        dual = other.dual;

        return *this;
    }

}

#endif // DUAL_QUATERNION_H