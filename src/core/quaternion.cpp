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

#include "quaternion.h"
#include <algorithm>
#include <math.h>

using namespace Try;

const Quaternion Quaternion::Zero = Quaternion();
const Quaternion Quaternion::Identity = Quaternion(0, 0, 0, 1);

Quaternion::Quaternion(float x, float y, float z, float w)
    : x(x),
      y(y),
      z(z),
      w(w)
{
}

Quaternion::Quaternion(const float components[4])
    : x(components[X]),
      y(components[Y]),
      z(components[Z]),
      w(components[W])
{
}

Quaternion::Quaternion(const Vector3& euler_angle)
{
    const float hroll = euler_angle.x * 0.5f;
    const float hpitch = euler_angle.y * 0.5f;
    const float hyaw = euler_angle.z * 0.5f;

    const float sx = sinf(hroll);
    const float cx = cosf(hroll);
    const float sy = sinf(hpitch);
    const float cy = cosf(hpitch);
    const float sz = sinf(hyaw);
    const float cz = cosf(hyaw);

    const float cycz = cy * cz;
    const float sysz = sy * sz;
    const float cysz = cy * sz;
    const float sycz = sy * cz;

    x = sx * cycz - cx * sysz;
    y = cx * sycz + sx * cysz;
    z = cx * cysz - sx * sycz;
    w = cx * cycz + sx * sysz;
}

Quaternion::Quaternion(float angle, const Vector3& axis)
{
    Vector3 naxis = axis.normalised();

    const float hangle = angle * DegToRad * 0.5f;
    const double sina = sinf(hangle);

    x = naxis.x * sina;
    y = naxis.y * sina;
    z = naxis.z * sina;
    w = cosf(hangle);
}

Quaternion::Quaternion(const Matrix3& m)
{
    float trace = m.m00 + m.m11 + m.m22;

    if (trace > 0)
    {
        const float s = 0.5f / sqrtf(trace + 1.0f);

        w = 0.25f / s;
        x = (m.m21 - m.m12) * s;
        y = (m.m02 - m.m20) * s;
        z = (m.m10 - m.m01) * s;

    }

    else
    {
        if (m.m00 > m.m11 && m.m00 > m.m22)
        {
            const float s = 2.0f * sqrtf(1.0f + m.m00 - m.m11 - m.m22);

            w = (m.m21 - m.m12) / s;
            x = 0.25f * s;
            y = (m.m01 + m.m10) / s;
            z = (m.m02 + m.m20) / s;
        }

        else if (m.m11 > m.m22)
        {
            const float s = 2.0f * sqrtf(1.0f + m.m11 - m.m00 - m.m22);

            w = (m.m02 - m.m20) / s;
            x = (m.m01 + m.m10 ) / s;
            y = 0.25f * s;
            z = (m.m12 + m.m21) / s;
        }

        else
        {
            const float s = 2.0f * sqrtf(1.0f + m.m22 - m.m00 - m.m11);

            w = (m.m10 - m.m01) / s;
            x = (m.m02 + m.m20) / s;
            y = (m.m12 + m.m21) / s;
            z = 0.25f * s;
        }
    }
}

Quaternion::Quaternion(const Quaternion& q)
    : x(q.x),
      y(q.y),
      z(q.z),
      w(q.w)
{
}

Quaternion& Quaternion::normalize()
{
    const float len = this->length();

    if (len > 0)
    {
        const double inv_len = 1.0f / len;

        w *= inv_len;
        x *= inv_len;
        y *= inv_len;
        z *= inv_len;
    }

    return *this;
}

Quaternion& Quaternion::invert()
{
    x = -x;
    y = -y;
    z = -z;

    return *this;
}

float Quaternion::length() const
{
    return sqrt(this->sqrLength());
}

float Quaternion::sqrLength() const
{
    return (w*w + x*x + y*y + z*z);
}

float Quaternion::dotProduct(const Quaternion& q) const
{
    return (x*q.x) + (y*q.y) + (z*q.z) + (w*q.w);
}

float Quaternion::angle() const
{
    if (this->sqrLength() > 0.0f)
        return 2.0f * acos(w);

    return 0;
}

Vector3 Quaternion::axis() const
{
    const float len = this->length();

    if (len > 0.0f)
    {
        float inv_len = 1.0f / len;

        return Vector3(
            x*inv_len,
            y*inv_len,
            z*inv_len
        );
    }

    // Any axis is valid because angle is 0.
    return Vector3::YAxis;
}

Vector3 Quaternion::toEulerAngle() const
{
    const double sqw = w*w;
    const double sqx = x*x;
    const double sqy = y*y;
    const double sqz = z*z;

    return Vector3(
        // Pitch.
        atan2(2 * (y * z + w * x), sqw - sqx - sqy + sqz),
        // Yaw.
        asin(-2 * (x * z - w * y)),
        // Roll.
        atan2(2 * (x * y + w * z), sqw + sqx - sqy - sqz)
    );
}

Matrix3 Quaternion::toMatrix() const
{
    const double sqx2 = x*x*2.0f;
    const double sqy2 = y*y*2.0f;
    const double sqz2 = z*z*2.0f;

    return Matrix3(
        1.0f - sqy2 - sqz2,
        2.0f * x * y + 2.0f * w * z,
        2.0f * x * z - 2.0f * w * y,
        2.0f * x * y - 2.0f * w * z,
        1.0f - sqx2 - sqz2,
        2.0f * y * z + 2.0f * w * x,
        2.0f * x * z + 2.0f * w * y,
        2.0f * y * z - 2.0f * w * x,
        1.0f - sqx2 - sqy2
    );
}

Quaternion Quaternion::normalised() const
{
    return Quaternion(*this).normalize();
}

Quaternion Quaternion::inverse() const
{
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::operator - () const
{
    return Quaternion(-x, -y, -z, -w);
}

Quaternion Quaternion::operator - (const Quaternion& q) const
{
    return Quaternion(x-q.x, y-q.y, z-q.z, w-q.w);
}

Quaternion Quaternion::operator + (const Quaternion& q) const
{
    return Quaternion(x+q.x, y+q.y, z+q.z, w+q.w);
}

Quaternion Quaternion::operator * (const Quaternion& q) const
{
    return Quaternion(
        (w * q.x) + (x * q.w) + (y * q.z) - (z * q.y), // x
        (w * q.y) + (y * q.w) + (z * q.x) - (x * q.z), // y
        (w * q.z) + (z * q.w) + (x * q.y) - (y * q.x), // z
        (w * q.w) - (x * q.x) - (y * q.y) - (z * q.z)  // w
    );
}

Quaternion Quaternion::operator * (float s) const
{
    return Quaternion(s*x, s*y, s*z, s*w);
}

Vector3 Quaternion::operator * (const Vector3& v) const
{
    Vector3 uv, uuv;
    Vector3 qvec(x, y, z);
    uv = qvec.crossProduct(v);
    uuv = qvec.crossProduct(uv);
    uv *= (2.0f * w);
    uuv *= 2.0f;

    return v + uv + uuv;
}

Quaternion& Quaternion::operator = (const Quaternion& q)
{
    x = q.x;
    y = q.y;
    z = q.z;
    w = q.w;

    return *this;
}

Quaternion& Quaternion::operator *= (float s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}

Quaternion& Quaternion::operator *= (const Quaternion& q)
{
    return (*this = q * (*this));
}

bool Quaternion::operator == (const Quaternion& q) const
{
    return ((x == q.x) &&
            (y == q.y) &&
            (z == q.z) &&
            (w == q.w));
}

bool Quaternion::operator != (const Quaternion& q) const
{
    return !(*this == q);
}

Quaternion Quaternion::lerp(Quaternion q1, Quaternion q2, float time)
{
    const float scale = 1.0f - time;

    return (q1*scale) + (q2*time);
}

Quaternion Quaternion::slerp(Quaternion q1, Quaternion q2, float time, float threshold)
{
    float angle = q1.dotProduct(q2);

    // Forces short rotation.
    if (angle < 0.0f)
    {
        q1 *= -1.0f;
        angle *= -1.0f;
    }

    // Spherical interpolation.
    if (angle <= (1-threshold))
    {
        const float theta = acosf(angle);
        const float invsintheta = 1.0f / (sinf(theta));
        const float scale = sinf(theta * (1.0f-time)) * invsintheta;
        const float invscale = sinf(theta * time) * invsintheta;

        return (q1*scale) + (q2*invscale);
    }

    // Linear interploation.
    else
        return Quaternion::lerp(q1,q2,time);
}

Quaternion Quaternion::rotationFromTo(const Vector3& from, const Vector3& to)
{
    Vector3 v0 = from;
    Vector3 v1 = to;

    v0.normalize();
    v1.normalize();

    const float d = v0.dotProduct(v1);

     // If dot == 1, vectors are the same.
    if (d >= 1.0f)
        return Quaternion::Identity;

    // Vectors are exactly the opposite.
    else if (d <= -1.0f)
    {
        Vector3 axis(1.0f, 0.f, 0.f);
        axis = axis.crossProduct(v0);

        if (axis.length() == 0)
        {
            axis = Vector3(0.f,1.f,0.f);
            axis.crossProduct(v0);
        }

        return Quaternion(axis.X, axis.Y, axis.Z, 0).normalize();
    }

    float s = sqrtf((1+d)*2);
    float invs = 1.f / s;
    Vector3 c = v0.crossProduct(v1)*invs;

    return Quaternion(c.x, c.y, c.z, s * 0.5f).normalize();
}

std::ostream& operator << (std::ostream& os, const Try::Quaternion& q)
{
    os << "Quaternion(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";

    return os;
}

