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

#include "matrix3.h"

using namespace Try;

const Matrix3 Matrix3::Zero = Matrix3();
const Matrix3 Matrix3::Identity = Matrix3(1,0,0,
                                          0,1,0,
                                          0,0,1);

Matrix3::Matrix3(float m00,float m01,float m02,
                 float m10,float m11,float m12,
                 float m20,float m21,float m22)
    : m00(m00), m01(m01), m02(m02),
      m10(m10), m11(m11), m12(m12),
      m20(m20), m21(m21), m22(m22)
{
}

Matrix3::~Matrix3()
{
}

Matrix3& Matrix3::transpose()
{
    float tmp[] = {
        m00, m10, m20,
        m01, m11, m21,
        m02, m12, m22
    };

    memcpy(components, tmp, 9*sizeof(float));

    return *this;
}

Matrix3& Matrix3::invert()
{
    memcpy(components, this->inverted().components, 9*sizeof(float));

    return *this;
}

void Matrix3::setRow(unsigned int r, const Vector3& values)
{
    unsigned int row = r % 3;

    m[row][0] = values.x;
    m[row][1] = values.y;
    m[row][2] = values.z;
}

void Matrix3::setColumn(unsigned int c, const Vector3& values)
{
    unsigned int column = c % 3;

    m[0][column] = values.x;
    m[1][column] = values.y;
    m[2][column] = values.z;
}

double Matrix3::determinant() const
{
    return m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 - m02*m11*m20;
}

Vector3 Matrix3::row(unsigned int row) const
{
    return Vector3(m[row % 3]);
}

Vector3 Matrix3::column(unsigned int col) const
{
    unsigned int column = col % 3;

    return Vector3(m[0][column],
                   m[1][column],
                   m[2][column]);
}

Matrix3 Matrix3::transposed() const
{
    return Matrix3(m00, m10, m20,
                   m01, m11, m21,
                   m02, m12, m22);
}

Matrix3 Matrix3::inverted() const
{
    Matrix3 m;
    double det = this->determinant();

    if (det != 0)
    {
        double t = 1.0f / det;

        m.m00 = (m11*m22 - m12*m21) * t;
        m.m01 = (m02*m21 - m01*m22) * t;
        m.m02 = (m01*m12 - m02*m11) * t;
        m.m10 = (m12*m20 - m10*m22) * t;
        m.m11 = (m00*m22 - m02*m20) * t;
        m.m12 = (m02*m10 - m00*m12) * t;
        m.m20 = (m10*m21 - m11*m20) * t;
        m.m21 = (m01*m20 - m00*m21) * t;
        m.m22 = (m00*m11 - m01*m10) * t;
    }

    return m;
}

Matrix3 Matrix3::operator - () const
{
    return Matrix3(-m00, -m01, -m02,
                   -m10, -m11, -m12,
                   -m20, -m21, -m22);
}

Matrix3 Matrix3::operator + (const Matrix3& mat) const
{
    return Matrix3(m00 + mat.m00, m01 + mat.m01, m02 + mat.m02,
                   m10 + mat.m00, m11 + mat.m11, m12 + mat.m12,
                   m20 + mat.m00, m21 + mat.m21, m22 + mat.m22);
}

Matrix3 Matrix3::operator - (const Matrix3& mat) const
{
    return Matrix3(m00 - mat.m00, m01 - mat.m01, m02 - mat.m02,
                   m10 - mat.m00, m11 - mat.m11, m12 - mat.m12,
                   m20 - mat.m00, m21 - mat.m21, m22 - mat.m22);
}

Matrix3 Matrix3::operator * (const Matrix3& mat) const
{
    Matrix3 result;

    result[0][0] = m00 * mat.m00 + m01 * mat.m10 + m02 * mat.m20;
    result[1][0] = m10 * mat.m00 + m11 * mat.m10 + m12 * mat.m20;
    result[2][0] = m20 * mat.m00 + m21 * mat.m10 + m22 * mat.m20;

    result[0][1] = m00 * mat.m01 + m01 * mat.m11 + m02 * mat.m21;
    result[1][1] = m10 * mat.m01 + m11 * mat.m11 + m12 * mat.m21;
    result[2][1] = m20 * mat.m01 + m21 * mat.m11 + m22 * mat.m21;

    result[0][2] = m00 * mat.m02 + m01 * mat.m12 + m02 * mat.m22;
    result[1][2] = m10 * mat.m02 + m11 * mat.m12 + m12 * mat.m22;
    result[2][2] = m20 * mat.m02 + m21 * mat.m12 + m22 * mat.m22;

    return result;
}

Vector3 Matrix3::operator * (const Vector3& vec) const
{
    return Vector3(m00 * vec.x + m01 * vec.y + m02 * vec.z,
                   m10 * vec.x + m11 * vec.y + m12 * vec.z,
                   m20 * vec.x + m21 * vec.y + m22 * vec.z);
}

Matrix3 Matrix3::operator * (float value) const
{
    return Matrix3(m00 * value, m01 * value, m02 * value,
                   m10 * value, m11 * value, m12 * value,
                   m20 * value, m21 * value, m22 * value);
}

Matrix3 Matrix3::operator / (float value) const
{
    if (value != 0)
    {
        float q = 1.0f / value;

        return (*this * q);
    }

    return Matrix3();
}

float* Matrix3::operator [] (unsigned char row)
{
    return m[row % 3];
}

const float* Matrix3::operator [] (unsigned char row) const
{
    return m[row % 3];
}

const Matrix3& Matrix3::operator = (const Matrix3& mat)
{
    m00 = mat.m00;	m01 = mat.m01;	m02 = mat.m02;

    m10 = mat.m10;	m11 = mat.m11;	m12 = mat.m12;

    m20 = mat.m20;	m21 = mat.m21;	m22 = mat.m22;

    return *this;
}

const Matrix3& Matrix3::operator += (const Matrix3& mat)
{
    m00 += mat.m00;	m01 += mat.m01;	m02 += mat.m02;

    m10 += mat.m10;	m11 += mat.m11;	m12 += mat.m12;

    m20 += mat.m20;	m21 += mat.m21;	m22 += mat.m22;

    return *this;
}

const Matrix3& Matrix3::operator -= (const Matrix3& mat)
{
    m00 -= mat.m00;	m01 -= mat.m01;	m02 -= mat.m02;

    m10 -= mat.m10;	m11 -= mat.m11;	m12 -= mat.m12;

    m20 -= mat.m20;	m21 -= mat.m21;	m22 -= mat.m22;

    return *this;
}

const Matrix3& Matrix3::operator *= (float value)
{
    m00 *= value;	m01 *= value;	m02 *= value;

    m10 *= value;	m11 *= value;	m12 *= value;

    m20 *= value;	m21 *= value;	m22 *= value;

    return *this;
}

const Matrix3& Matrix3::operator /= (float value)
{
    if (value != 0)
    {
        float q = 1.0f / value;

        *this *= q;
    }

    return *this;
}

bool Matrix3::operator == (const Matrix3& mat) const
{
    return ((mat.m00 == m00) && (mat.m01 == m01) && (mat.m02 == m02) &&
            (mat.m10 == m10) && (mat.m11 == m11) && (mat.m12 == m12) &&
            (mat.m20 == m20) && (mat.m21 == m21) && (mat.m22 == m22));
}

bool Matrix3::operator != (const Matrix3& mat) const
{
    return !(*this == mat);
}

bool Matrix3::isDiagonal() const
{
    return (m01 == m02 == m10 == m12 == m20 == m21 == 0.0f);
}

std::ostream& operator << (std::ostream& os, const Try::Matrix3& m)
{
    os << "Matrix3(" << m.m00 << ", " << m.m01 << ", " << m.m02 << ", " << std::endl;
    os               << m.m10 << ", " << m.m11 << ", " << m.m12 << ", " << std::endl;
    os               << m.m20 << ", " << m.m21 << ", " << m.m22 << ")"  << std::endl;

    return os;
}
