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

#ifndef TRY_VECTOR4_H
#define TRY_VECTOR4_H

#include "alias.h"

namespace Try
{
    class Vector4
    {
    public:
        enum Components { X, Y, Z, W };

        static const Vector4 Zero;
        static const Vector4 Identity;

        union
        {
            float components[4];
            struct
            {
                 float x, y, z, w;
            };
        };

    public:
        Vector4(float x = 0, float y = 0, float z = 0, float w = 0);
        Vector4(const float components[4]);
        Vector4(const Vector4& v);

        Vector4& normalize();

        float length() const;
        float sqrLength() const;
        float dotProduct(const Vector4& v) const;

        const Vector4 operator + (const Vector4& v) const;
        const Vector4 operator - (const Vector4& v) const;
        const Vector4 operator * (float k) const;
        const Vector4 operator / (float k) const;

        float& operator [] (unsigned char i);
        const float operator [] (unsigned char i) const;

        Vector4& operator = (const Vector4& v);
        Vector4& operator += (const Vector4& v);
        Vector4& operator -= (const Vector4& v);
        Vector4& operator *= (float k);
        Vector4& operator /= (float k);

        Vector4 normalised() const;
        Vector4 operator - () const;

        bool operator == (const Vector4& v) const;
        bool operator != (const Vector4& v) const;
    };
}

std::ostream& operator << (std::ostream& os, const Try::Vector4& v);

#endif // TRY_VECTOR4_H
