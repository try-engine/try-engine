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

#include "matrix4.h"

using namespace Try;

const Matrix4 Matrix4::Zero = Matrix4();
const Matrix4 Matrix4::Identity = Matrix4(1,0,0,0,
                                          0,1,0,0,
                                          0,0,1,0,
                                          0,0,0,1);

Matrix4::Matrix4(float m00,float m01,float m02,float m03,
                 float m10,float m11,float m12,float m13,
                 float m20,float m21,float m22,float m23,
                 float m30,float m31,float m32,float m33)
    : m00(m00), m01(m01), m02(m02), m03(m03),
      m10(m10), m11(m11), m12(m12), m13(m13),
      m20(m20), m21(m21), m22(m22), m23(m23),
      m30(m30), m31(m31), m32(m32), m33(m33)
{
}

Matrix4::~Matrix4()
{
}

Matrix4& Matrix4::transpose()
{
    Vector4 c0 = this->column(0);
    Vector4 c1 = this->column(1);
    Vector4 c2 = this->column(2);
    Vector4 c3 = this->column(3);

    memcpy(r0, c0.components, 4);
    memcpy(r1, c1.components, 4);
    memcpy(r2, c2.components, 4);
    memcpy(r3, c3.components, 4);

    return *this;
}

Matrix4& Matrix4::invert()
{
    memcpy(components, this->inverted().components, 16*sizeof(float));

    return *this;
}

void Matrix4::setRow(unsigned int r, const Vector4& values)
{
    unsigned int row = r % 4;

    m[row][0] = values.x;
    m[row][1] = values.y;
    m[row][2] = values.z;
    m[row][3] = values.w;
}

void Matrix4::setColumn(unsigned int c, const Vector4& values)
{
    unsigned int column = c % 4;

    m[0][column] = values.x;
    m[1][column] = values.y;
    m[2][column] = values.z;
    m[3][column] = values.w;
}

double Matrix4::determinant() const
{
    return m03*m12*m21*m30 - m02*m13*m21*m30 - m03*m11*m22*m30 + m01*m13*m22*m30 +
           m02*m11*m23*m30 - m01*m12*m23*m30 - m03*m12*m20*m31 + m02*m13*m20*m31 +
           m03*m10*m22*m31 - m00*m13*m22*m31 - m02*m10*m23*m31 + m00*m12*m23*m31 +
           m03*m11*m20*m32 - m01*m13*m20*m32 - m03*m10*m21*m32 + m00*m13*m21*m32 +
           m01*m10*m23*m32 - m00*m11*m23*m32 - m02*m11*m20*m33 + m01*m12*m20*m33 +
           m02*m10*m21*m33 - m00*m12*m21*m33 - m01*m10*m22*m33 + m00*m11*m22*m33;
}

Vector4 Matrix4::row(unsigned int row) const
{
    return Vector4(m[row % 4]);
}

Vector4 Matrix4::column(unsigned int col) const
{
    unsigned int column = col % 4;

    return Vector4(m[0][column],
                   m[1][column],
                   m[2][column],
                   m[3][column]);
}

Matrix4 Matrix4::transposed() const
{
    return Matrix4(m00, m10, m20, m30,
                   m01, m11, m21, m31,
                   m02, m12, m22, m32,
                   m03, m13, m23, m33);
}

Matrix4 Matrix4::inverted() const
{
    Matrix4 m;

    double det = this->determinant();

    if (det != 0)
    {
        double t = 1.0f / det;

        m.m00 = (m12*m23*m31 - m13*m22*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 + m11*m22*m33) * t;
        m.m01 = (m03*m22*m31 - m02*m23*m31 - m03*m21*m32 + m01*m23*m32 + m02*m21*m33 - m01*m22*m33) * t;
        m.m02 = (m02*m13*m31 - m03*m12*m31 + m03*m11*m32 - m01*m13*m32 - m02*m11*m33 + m01*m12*m33) * t;
        m.m03 = (m03*m12*m21 - m02*m13*m21 - m03*m11*m22 + m01*m13*m22 + m02*m11*m23 - m01*m12*m23) * t;
        m.m10 = (m13*m22*m30 - m12*m23*m30 - m13*m20*m32 + m10*m23*m32 + m12*m20*m33 - m10*m22*m33) * t;
        m.m11 = (m02*m23*m30 - m03*m22*m30 + m03*m20*m32 - m00*m23*m32 - m02*m20*m33 + m00*m22*m33) * t;
        m.m12 = (m03*m12*m30 - m02*m13*m30 - m03*m10*m32 + m00*m13*m32 + m02*m10*m33 - m00*m12*m33) * t;
        m.m13 = (m02*m13*m20 - m03*m12*m20 + m03*m10*m22 - m00*m13*m22 - m02*m10*m23 + m00*m12*m23) * t;
        m.m20 = (m11*m23*m30 - m13*m21*m30 + m13*m20*m31 - m10*m23*m31 - m11*m20*m33 + m10*m21*m33) * t;
        m.m21 = (m03*m21*m30 - m01*m23*m30 - m03*m20*m31 + m00*m23*m31 + m01*m20*m33 - m00*m21*m33) * t;
        m.m22 = (m01*m13*m30 - m03*m11*m30 + m03*m10*m31 - m00*m13*m31 - m01*m10*m33 + m00*m11*m33) * t;
        m.m23 = (m03*m11*m20 - m01*m13*m20 - m03*m10*m21 + m00*m13*m21 + m01*m10*m23 - m00*m11*m23) * t;
        m.m30 = (m12*m21*m30 - m11*m22*m30 - m12*m20*m31 + m10*m22*m31 + m11*m20*m32 - m10*m21*m32) * t;
        m.m31 = (m01*m22*m30 - m02*m21*m30 + m02*m20*m31 - m00*m22*m31 - m01*m20*m32 + m00*m21*m32) * t;
        m.m32 = (m02*m11*m30 - m01*m12*m30 - m02*m10*m31 + m00*m12*m31 + m01*m10*m32 - m00*m11*m32) * t;
        m.m33 = (m01*m12*m20 - m02*m11*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 + m00*m11*m22) * t;
    }

    return m;
}

Matrix4 Matrix4::operator - () const
{
    return Matrix4(-m00, -m10, -m20, -m30,
                   -m01, -m11, -m21, -m31,
                   -m02, -m12, -m22, -m32,
                   -m03, -m13, -m23, -m33);
}

Matrix4 Matrix4::operator + (const Matrix4& mat) const
{
    return Matrix4(m00 + mat.m00, m01 + mat.m01, m02 + mat.m02, m03 + mat.m03,
                   m10 + mat.m00, m11 + mat.m11, m12 + mat.m12, m13 + mat.m13,
                   m20 + mat.m00, m21 + mat.m21, m22 + mat.m22, m23 + mat.m23,
                   m30 + mat.m30, m31 + mat.m31, m32 + mat.m32, m33 + mat.m33);
}

Matrix4 Matrix4::operator - (const Matrix4& mat) const
{
    return Matrix4(m00 - mat.m00, m01 - mat.m01, m02 - mat.m02, m03 - mat.m03,
                   m10 - mat.m00, m11 - mat.m11, m12 - mat.m12, m13 - mat.m13,
                   m20 - mat.m00, m21 - mat.m21, m22 - mat.m22, m23 - mat.m23,
                   m30 - mat.m30, m31 - mat.m31, m32 - mat.m32, m33 - mat.m33);
}

Matrix4 Matrix4::operator * (const Matrix4& mat) const
{
    return Matrix4(m00*mat.m00 + m01*mat.m10 + m02*mat.m20 + m03*mat.m30,
                   m00*mat.m01 + m01*mat.m11 + m02*mat.m21 + m03*mat.m31,
                   m00*mat.m02 + m01*mat.m12 + m02*mat.m22 + m03*mat.m32,
                   m00*mat.m03 + m01*mat.m13 + m02*mat.m23 + m03*mat.m33,
                   m10*mat.m00 + m11*mat.m10 + m12*mat.m20 + m13*mat.m30,
                   m10*mat.m01 + m11*mat.m11 + m12*mat.m21 + m13*mat.m31,
                   m10*mat.m02 + m11*mat.m12 + m12*mat.m22 + m13*mat.m32,
                   m10*mat.m03 + m11*mat.m13 + m12*mat.m23 + m13*mat.m33,
                   m20*mat.m00 + m21*mat.m10 + m22*mat.m20 + m23*mat.m30,
                   m20*mat.m01 + m21*mat.m11 + m22*mat.m21 + m23*mat.m31,
                   m20*mat.m02 + m21*mat.m12 + m22*mat.m22 + m23*mat.m32,
                   m20*mat.m03 + m21*mat.m13 + m22*mat.m23 + m23*mat.m33,
                   m30*mat.m00 + m31*mat.m10 + m32*mat.m20 + m33*mat.m30,
                   m30*mat.m01 + m31*mat.m11 + m32*mat.m21 + m33*mat.m31,
                   m30*mat.m02 + m31*mat.m12 + m32*mat.m22 + m33*mat.m32,
                   m30*mat.m03 + m31*mat.m13 + m32*mat.m23 + m33*mat.m33);
}

Vector4	Matrix4::operator * (const Vector4& vec) const
{
    return Vector4(m00*vec.x + m01*vec.y + m02*vec.z + m03*vec.w,
                   m10*vec.x + m11*vec.y + m12*vec.z + m13*vec.w,
                   m20*vec.x + m21*vec.y + m22*vec.z + m23*vec.w,
                   m30*vec.x + m31*vec.y + m32*vec.z + m33*vec.w);
}

Matrix4 Matrix4::operator * (float value) const
{
    return Matrix4(m00 * value, m01 * value, m02 * value, m03 * value,
                   m10 * value, m11 * value, m12 * value, m13 * value,
                   m20 * value, m21 * value, m22 * value, m23 * value,
                   m30 * value, m31 * value, m32 * value, m33 * value);
}

Matrix4 Matrix4::operator / (float value) const
{
    if (value != 0)
    {
        float q = 1.0f / value;

        return (*this * q);
    }

    return Matrix4();
}

float* Matrix4::operator [] (unsigned char row)
{
    return m[row % 4];
}

const float* Matrix4::operator [] (unsigned char row) const
{
    return m[row % 4];
}

const Matrix4& Matrix4::operator =  (const Matrix4& mat)
{
    m00 = mat.m00;	m01 = mat.m01;	m02 = mat.m02;  m03 = mat.m03;

    m10 = mat.m10;	m11 = mat.m11;	m12 = mat.m12;  m13 = mat.m13;

    m20 = mat.m20;	m21 = mat.m21;	m22 = mat.m22;  m23 = mat.m23;

    m30 = mat.m30;	m31 = mat.m31;	m32 = mat.m32;  m33 = mat.m33;

    return *this;
}

const Matrix4& Matrix4::operator += (const Matrix4& mat)
{
    m00 += mat.m00;	m01 += mat.m01;	m02 += mat.m02;  m03 += mat.m03;

    m10 += mat.m10;	m11 += mat.m11;	m12 += mat.m12;  m13 += mat.m13;

    m20 += mat.m20;	m21 += mat.m21;	m22 += mat.m22;  m23 += mat.m23;

    m30 += mat.m30;	m31 += mat.m31;	m32 += mat.m32;  m33 += mat.m33;

    return *this;
}

const Matrix4& Matrix4::operator -= (const Matrix4& mat)
{
    m00 -= mat.m00;	m01 -= mat.m01;	m02 -= mat.m02;  m03 -= mat.m03;

    m10 -= mat.m10;	m11 -= mat.m11;	m12 -= mat.m12;  m13 -= mat.m13;

    m20 -= mat.m20;	m21 -= mat.m21;	m22 -= mat.m22;  m23 -= mat.m23;

    m30 -= mat.m30;	m31 -= mat.m31;	m32 -= mat.m32;  m33 -= mat.m33;

    return *this;
}

const Matrix4& Matrix4::operator *= (float value)
{
    m00 *= value;	m01 *= value;	m02 *= value;  m03 *= value;

    m10 *= value;	m11 *= value;	m12 *= value;  m13 *= value;

    m20 *= value;	m21 *= value;	m22 *= value;  m23 *= value;

    m30 *= value;	m31 *= value;	m32 *= value;  m33 *= value;

    return *this;
}

const Matrix4& Matrix4::operator /= (float value)
{
    if (value != 0)
    {
        float q = 1.0f / value;

        *this *= q;
    }

    return *this;
}

bool Matrix4::operator == (const Matrix4& mat) const
{
    return ((mat.m00 == m00) && (mat.m01 == m01) && (mat.m02 == m02) && (mat.m03 == m03) &&
            (mat.m10 == m10) && (mat.m11 == m11) && (mat.m12 == m12) && (mat.m13 == m13) &&
            (mat.m20 == m20) && (mat.m21 == m21) && (mat.m22 == m22) && (mat.m23 == m23) &&
            (mat.m30 == m30) && (mat.m31 == m31) && (mat.m32 == m32) && (mat.m33 == m33));
}

bool Matrix4::operator != (const Matrix4& mat) const
{
    return !(*this == mat);
}

bool Matrix4::isDiagonal() const
{
    return (m01 == m02 == m03 == m10 == m12 == m13 == m20 == m21 == m23 == m30 == m31 == m32 == 0);
}

std::ostream& operator << (std::ostream& os, const Try::Matrix4& m)
{
    os << "Matrix4(" << m.m00 << ", " << m.m01 << ", " << m.m02 << ", " << m.m03 << ", " << std::endl;
    os               << m.m10 << ", " << m.m11 << ", " << m.m12 << ", " << m.m13 << ", " << std::endl;
    os               << m.m20 << ", " << m.m21 << ", " << m.m22 << ", " << m.m23 << ", " << std::endl;
    os               << m.m30 << ", " << m.m31 << ", " << m.m32 << ", " << m.m33 << ")"  << std::endl;

    return os;
}
