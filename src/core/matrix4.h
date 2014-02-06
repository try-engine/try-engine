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

#ifndef TRY_MATRIX4_H
#define TRY_MATRIX4_H

#include "vector4.h"

namespace Try
{
    class Matrix4
    {
    public:
        static const Matrix4 Zero;
        static const Matrix4 Identity;

        union {
            float	m[4][4];
            struct {
                float r0[4];
                float r1[4];
                float r2[4];
                float r3[4];
            };
            struct {
                float m00, m01, m02, m03;
                float m10, m11, m12, m13;
                float m20, m21, m22, m23;
                float m30, m31, m32, m33;
            };
            float components[16];
        };

    public:
        Matrix4(float m00 = 0, float m01 = 0, float m02 = 0, float m03 = 0,
                float m10 = 0, float m11 = 0, float m12 = 0, float m13 = 0,
                float m20 = 0, float m21 = 0, float m22 = 0, float m23 = 0,
                float m30 = 0, float m31 = 0, float m32 = 0, float m33 = 0);
        ~Matrix4();

        Matrix4& transpose();
        Matrix4& invert();

        double determinant() const;

        void setRow(unsigned int r, const Vector4& values);
        void setColumn(unsigned int c, const Vector4& values);

        Vector4 row(unsigned int r) const;
        Vector4 column(unsigned int c) const;

        Matrix4 transposed() const;
        Matrix4 inverted() const;
        Matrix4 operator - () const;

        Matrix4 operator + (const Matrix4& mat) const;
        Matrix4 operator - (const Matrix4& mat) const;
        Matrix4 operator * (const Matrix4& mat) const;
        Vector4	operator * (const Vector4& vec) const;
        Matrix4 operator * (float value) const;
        Matrix4 operator / (float value) const;

        float* operator [] (unsigned char row);
        const float* operator [] (unsigned char row) const;

        const Matrix4& operator =  (const Matrix4& mat);
        const Matrix4& operator += (const Matrix4& mat);
        const Matrix4& operator -= (const Matrix4& mat);
        const Matrix4& operator *= (float value);
        const Matrix4& operator /= (float value);

        bool operator == (const Matrix4& mat) const;
        bool operator != (const Matrix4& mat) const;

        bool isDiagonal() const;

        template<class T>
        static Matrix4 from(const T& src);
    };

    template<class T>
    Matrix4 Matrix4::from(const T& src)
    {
        return Matrix4(
            src[0][0], src[1][0], src[2][0], src[3][0],
            src[0][1], src[1][1], src[2][1], src[3][1],
            src[0][2], src[1][2], src[2][2], src[3][2],
            src[0][3], src[1][3], src[2][3], src[3][3]
        );
    }
}

std::ostream& operator << (std::ostream& os, const Try::Matrix4& m);

#endif // TRY_MATRIX4_H
