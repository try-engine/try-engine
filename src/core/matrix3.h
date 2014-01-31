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

#ifndef TRY_MATRIX3_H
#define TRY_MATRIX3_H

#include "vector3.h"

namespace Try
{
    class Matrix3
    {
    public:
        static const Matrix3 Zero;
        static const Matrix3 Identity;

        union {
            float	m[3][3];
            struct {
                float r0[3];
                float r1[3];
                float r2[3];
            };
            struct {
                float m00, m01, m02;
                float m10, m11, m12;
                float m20, m21, m22;
            };
            float components[9];
        };

    public:
        Matrix3(float m00 = 0, float m01 = 0, float m02 = 0,
                float m10 = 0, float m11 = 0, float m12 = 0,
                float m20 = 0, float m21 = 0, float m22 = 0);
        ~Matrix3();

        Matrix3& transpose();
        Matrix3& invert();

        void setRow(unsigned int r, const Vector3& values);
        void setColumn(unsigned int c, const Vector3& values);

        double determinant() const;

        Vector3 row(unsigned int r) const;
        Vector3 column(unsigned int c) const;

        Matrix3 transposed() const;
        Matrix3 inverted() const;
        Matrix3 operator - () const;

        Matrix3 operator + (const Matrix3& mat) const;
        Matrix3 operator - (const Matrix3& mat) const;
        Matrix3 operator * (const Matrix3& mat) const;
        Vector3	operator * (const Vector3& vec) const;
        Matrix3 operator * (float value) const;
        Matrix3 operator / (float value) const;

        float* operator [] (unsigned char row);
        const float* operator [] (unsigned char row) const;

        const Matrix3& operator =  (const Matrix3& mat);
        const Matrix3& operator += (const Matrix3& mat);
        const Matrix3& operator -= (const Matrix3& mat);
        const Matrix3& operator *= (float value);
        const Matrix3& operator /= (float value);

        bool operator == (const Matrix3& mat) const;
        bool operator != (const Matrix3& mat) const;

        bool isDiagonal() const;
    };
}

std::ostream& operator << (std::ostream& os, const Try::Matrix3& m);

#endif // TRY_MATRIX3_H
