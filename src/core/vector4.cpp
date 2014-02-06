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

#include "vector4.h"

using namespace Try;

const Vector4 Vector4::Zero = Vector4();
const Vector4 Vector4::Identity = Vector4(1, 1, 1, 1);

Vector4::Vector4(float x, float y, float z, float w)
    : x(x),
      y(y),
      z(z),
      w(w)
{
}

Vector4::Vector4(const float components[4])
    : x(components[0]),
      y(components[1]),
      z(components[2]),
      w(components[3])
{
}

Vector4::Vector4(const Vector4& v)
    : x(v.x),
      y(v.y),
      z(v.z),
      w(v.w)
{
}

Vector4& Vector4::normalize()
{
    float length = this->length();

    if (length > 0.0f)
    {
        float temp = (1 / length);

        x *= temp;
        y *= temp;
        z *= temp;
        w *= temp;
    }

    return *this;
}

float Vector4::length() const
{
    return sqrt(this->sqrLength());
}

float Vector4::sqrLength() const
{
    return ((x * x) + (y * y) + (z * z) + (w * w));
}

float Vector4::dotProduct(const Vector4& v) const
{
    return ((x * v.x) + (y * v.y) + (z * v.z) + (w * v.w));
}

Vector4 Vector4::operator + (const Vector4& v) const
{
    return Vector4((x + v.x), (y + v.y), (z + v.z), (w + v.w));
}

Vector4 Vector4::operator - (const Vector4& v) const
{
    return Vector4((x - v.x), (y - v.y), (z - v.z), (w - v.w));
}

Vector4 Vector4::operator * (float k) const
{
    return Vector4((x * k), (y * k), (z * k), (w * k));
}

Vector4 Vector4::operator / (float k) const
{
    if (k == 0.0f)
        return *this;

    float temp = (1 / k);

    return Vector4((x * temp), (y * temp), (z * temp), (w * temp));
}

float& Vector4::operator [] (unsigned char i)
{
    assert(i < 4);
    return components[i];
}

const float Vector4::operator [] (unsigned char i) const
{
    assert(i < 4);
    return components[i];
}

Vector4& Vector4::Vector4::operator = (const Vector4& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;

    return *this;
}

Vector4& Vector4::Vector4::operator += (const Vector4& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;

    return *this;
}

Vector4& Vector4::Vector4::operator -= (const Vector4& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;

    return *this;
}

Vector4& Vector4::Vector4::operator *= (float k)
{
    x *= k;
    y *= k;
    z *= k;
    w *= k;

    return *this;
}

Vector4& Vector4::Vector4::operator /= (float k)
{
    if (k == 0.0f)
        return *this;

    float temp = 1 / k;

    x *= temp;
    y *= temp;
    z *= temp;
    w *= temp;

    return *this;
}

Vector4 Vector4::normalised() const
{
    Vector4 v(*this);

    v.normalize();

    return v;
}

Vector4 Vector4::operator - () const
{
    return Vector4(-x, -y, -z, -w);
}

bool Vector4::operator == (const Vector4& v) const
{
    return ((x == v.x) && (y == v.y) && (z == v.z) && (w == v.w));
}

bool Vector4::operator != (const Vector4& v) const
{
    return ((x != v.x) || (y != v.y) || (z != v.z) || (w != v.w));
}

std::ostream& operator << (std::ostream& os, const Try::Vector4& v)
{
    os << "Vector4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";

    return os;
}
