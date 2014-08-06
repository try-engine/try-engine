/*
 * This file is part of the Try! Engine project.
 *
 * Copyright 2010-2011 Emanuele Bertoldi. All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the modified BSD License along with this
 * program. If not, see <http://www.opensource.org/licenses/bsd-license.php>
 */

#ifndef TRY_QUATERNION_H
#define TRY_QUATERNION_H

#include <core/vector3.h>
#include <core/matrix3.h>

namespace Try
{
    class Quaternion
    {
    public:
        enum Components { X, Y, Z, W };

        static const Quaternion Zero;
        static const Quaternion Identity;

        union {
            float components[4];
            struct {
                float x;
                float y;
                float z;
                float w;
            };
        };

    public:
        Quaternion(float x = 0, float y = 0, float z = 0, float w = 0);
        Quaternion(const float components[4]);
        // "eurler_angle" must be expressed in radians.
        Quaternion(const Vector3& euler_angle);
        Quaternion(float angle, const Vector3& axis);
        Quaternion(const Matrix3& m);
        Quaternion(const Quaternion& q);

        Quaternion& normalize();
        Quaternion& invert();

        float length() const;
        float sqrLength() const;
        float dotProduct(const Quaternion& q) const;
        float angle() const;
        Vector3 axis() const;
        Vector3 toEulerAngle() const;
        Matrix3 toMatrix() const;
        Quaternion normalised() const;
        Quaternion inverse() const;

        Quaternion operator - () const;
        Quaternion operator - (const Quaternion& q) const;
        Quaternion operator + (const Quaternion& q) const;
        Quaternion operator * (const Quaternion& q) const;
        Quaternion operator * (float s) const;
        Vector3 operator * (const Vector3& v) const;

        Quaternion& operator = (const Quaternion& q);
        Quaternion& operator *= (const Quaternion& q);
        Quaternion& operator *= (float s);

        bool operator == (const Quaternion& q) const;
        bool operator != (const Quaternion& q) const;

        // Returns the linear interpolation between two quaternions.
        static Quaternion lerp(Quaternion q1, Quaternion q2, float time);

        // Returns the spherical interpolation between two quaternions.
        static Quaternion slerp(Quaternion q1, Quaternion q2, float time, float threshold=.05f);

        // Returns a quaternion which represents a rotation from one vector to another.
        static Quaternion rotationFromTo(const Vector3& from, const Vector3& to);

        template<typename T>
        static Quaternion from(const T& src);
    };

    template<typename T>
    Quaternion Quaternion::from(const T& src)
    {
        return Quaternion(src.x, src.y, src.z, src.w);
    }
}

std::ostream& operator << (std::ostream& os, const Try::Quaternion& q);

#endif // TRY_QUATERNION_H
