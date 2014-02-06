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

#ifndef TRY_VECTOR3_H
#define TRY_VECTOR3_H

#include "alias.h"

namespace Try
{
    class Vector3
    {
    public:
        enum Components { X, Y, Z };

        static const Vector3 Zero;
        static const Vector3 Identity;
        static const Vector3 XAxis;
        static const Vector3 YAxis;
        static const Vector3 ZAxis;

        union
        {
            float components[3];
            struct
            {
                 float x, y, z;
            };
        };

    public:
        Vector3(float x = 0, float y = 0, float z = 0);
        Vector3(const float components[3]);
        Vector3(const Vector3& v);

        Vector3& normalize();

        float length() const;
        float sqrLength() const;
        float distance(const Vector3& v) const;
        float sqrDistance(const Vector3& v) const;
        float angleBetween(const Vector3& v) const;
        float dotProduct(const Vector3& v) const;

        Vector3 crossProduct(const Vector3& v) const;

        Vector3 operator + (const Vector3& v) const;
        Vector3 operator - (const Vector3& v) const;
        Vector3 operator * (const Vector3& v) const;
        Vector3 operator * (float w) const;
        Vector3 operator / (float w) const;

        float& operator [] (unsigned char i);
        const float operator [] (unsigned char i) const;

        Vector3& operator = (const Vector3& v);
        Vector3& operator += (const Vector3& v);
        Vector3& operator -= (const Vector3& v);
        Vector3& operator *= (float w);
        Vector3& operator /= (float w);

        Vector3 normalised() const;
        Vector3 operator - () const;

        bool operator == (const Vector3& v) const;
        bool operator != (const Vector3& v) const;

        template<typename T>
        static Vector3 from(const T& src);
    };

    template<typename T>
    Vector3 Vector3::from(const T& src)
    {
        return Vector3(src.x, src.y, src.z);
    }
}

std::ostream& operator << (std::ostream& os, const Try::Vector3& v);

#endif // TRY_VECTOR3_H
