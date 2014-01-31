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

#include "vector3.h"

using namespace Try;

const Vector3 Vector3::Zero = Vector3();
const Vector3 Vector3::Identity = Vector3(1, 1, 1);
const Vector3 Vector3::XAxis = Vector3(1, 0, 0);
const Vector3 Vector3::YAxis = Vector3(0, 1, 0);
const Vector3 Vector3::ZAxis = Vector3(0, 0, 1);

Vector3::Vector3(float x, float y, float z)
    : x(x),
      y(y),
      z(z)
{
}

Vector3::Vector3(const float components[3])
    : x(components[0]),
      y(components[1]),
      z(components[2])
{
}

Vector3::Vector3(const Vector3& v)
    : x(v.x),
      y(v.y),
      z(v.z)
{
}

Vector3& Vector3::normalize()
{
    float length = this->length();

    if (length > 0.0f)
    {
        float temp = (1 / length);

        x *= temp;
        y *= temp;
        z *= temp;
    }

    return *this;
}

float Vector3::length() const
{
    return sqrt(this->sqrLength());
}

float Vector3::sqrLength() const
{
    return ((x * x) + (y * y) + (z * z));
}

float Vector3::distance(const Vector3& v) const
{
    return sqrt(this->sqrDistance(v));
}

float Vector3::sqrDistance(const Vector3& v) const
{
    float tx = x - v.x;
    float ty = y - v.y;
    float tz = z - v.z;

    return (tx * tx) + (ty * ty) + (tz * tz);
}

float Vector3::angleBetween(const Vector3& v) const
{
    Vector3 v1n = this->normalised();
    Vector3 v2n = v.normalised();

    float temp = v1n.length();
    if ((temp == 0.0f) || (v2n.length() == 0.0f))
        return temp;

    return acos(this->dotProduct(v));
}

float Vector3::dotProduct(const Vector3& v) const
{
    return ((x * v.x) + (y * v.y) + (z * v.z));
}

Vector3 Vector3::crossProduct(const Vector3& v) const
{
    return Vector3(((y * v.z) - (z * v.y)), ((z * v.x) - (x * v.z)), ((x * v.y) - (y * v.x)));
}

const Vector3 Vector3::operator + (const Vector3& v) const
{
    return Vector3((x + v.x), (y + v.y), (z + v.z));
}

const Vector3 Vector3::operator - (const Vector3& v) const
{
    return Vector3((x - v.x), (y - v.y), (z - v.z));
}

const Vector3 Vector3::operator * (float w) const
{
    return Vector3((x * w), (y * w), (z * w));
}

const Vector3 Vector3::operator / (float w) const
{
    if (w == 0.0f)
        return *this;

    float temp = (1 / w);

    return Vector3((x * temp), (y * temp), (z * temp));
}

float& Vector3::operator [] (unsigned char i)
{
    assert(i < 3);
    return components[i];
}

const float Vector3::operator [] (unsigned char i) const
{
    assert(i < 3);
    return components[i];
}

Vector3& Vector3::Vector3::operator = (const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

Vector3& Vector3::Vector3::operator += (const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vector3& Vector3::Vector3::operator -= (const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

Vector3& Vector3::Vector3::operator *= (float w)
{
    x *= w;
    y *= w;
    z *= w;

    return *this;
}

Vector3& Vector3::Vector3::operator /= (float w)
{
    if (w == 0.0f)
        return *this;

    float temp = 1 / w;

    x *= temp;
    y *= temp;
    z *= temp;

    return *this;
}

Vector3 Vector3::normalised() const
{
    Vector3 v(*this);

    v.normalize();

    return v;
}

Vector3 Vector3::operator - () const
{
    return Vector3(-x, -y, -z);
}

bool Vector3::operator == (const Vector3& v) const
{
    return ((x == v.x) && (y == v.y) && (z == v.z));
}

bool Vector3::operator != (const Vector3& v) const
{
    return ((x != v.x) || (y != v.y) || (z != v.z));
}

std::ostream& operator << (std::ostream& os, const Try::Vector3& v)
{
    os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";

    return os;
}
