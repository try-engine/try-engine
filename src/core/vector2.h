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

#ifndef TRY_VECTOR2_H
#define TRY_VECTOR2_H

#include "alias.h"

namespace Try
{
    class Vector2
    {
    public:
        enum Components { X, Y };

        static const Vector2 Zero;
        static const Vector2 Identity;
        static const Vector2 XAxis;
        static const Vector2 YAxis;

        union
        {
            float components[2];
            struct
            {
                 float x, y;
            };
        };

    public:
        Vector2(float x = 0, float y = 0);
        Vector2(const float components[2]);
        Vector2(const Vector2& v);

        Vector2& normalize();

        float length() const;
        float sqrLength() const;
        float distance(const Vector2& v) const;
        float sqrDistance(const Vector2& v) const;
        float angleBetween(const Vector2& v) const;
        float dotProduct(const Vector2& v) const;

        const Vector2 operator + (const Vector2& v) const;
        const Vector2 operator - (const Vector2& v) const;
        const Vector2 operator * (float w) const;
        const Vector2 operator / (float w) const;

        float& operator [] (unsigned char i);
        const float operator [] (unsigned char i) const;

        Vector2& operator = (const Vector2& v);
        Vector2& operator += (const Vector2& v);
        Vector2& operator -= (const Vector2& v);
        Vector2& operator *= (float w);
        Vector2& operator /= (float w);

        Vector2 normalised() const;
        Vector2 operator - () const;

        bool operator == (const Vector2& v) const;
        bool operator != (const Vector2& v) const;
    };
}

std::ostream& operator << (std::ostream& os, const Try::Vector2& v);

#endif // TRY_VECTOR2_H
