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

#include "vector2.h"

using namespace Try;

const Vector2 Vector2::Zero = Vector2();
const Vector2 Vector2::Identity = Vector2(1, 1);
const Vector2 Vector2::XAxis = Vector2(1, 0);
const Vector2 Vector2::YAxis = Vector2(0, 1);

Vector2::Vector2(float x, float y)
    : x(x),
      y(y)
{
}

Vector2::Vector2(const float components[3])
    : x(components[0]),
      y(components[1])
{
}

Vector2::Vector2(const Vector2& v)
    : x(v.x),
      y(v.y)
{
}

Vector2& Vector2::normalize()
{
    float length = this->length();

    if (length > 0.0f)
    {
        float temp = (1 / length);

        x *= temp;
        y *= temp;
    }

    return *this;
}

float Vector2::length() const
{
    return sqrt(this->sqrLength());
}

float Vector2::sqrLength() const
{
    return ((x * x) + (y * y));
}

float Vector2::distance(const Vector2& v) const
{
    return sqrt(this->sqrDistance(v));
}

float Vector2::sqrDistance(const Vector2& v) const
{
    float tx = x - v.x;
    float ty = y - v.y;

    return (tx * tx) + (ty * ty);
}

float Vector2::angleBetween(const Vector2& v) const
{
    Vector2 v1n = this->normalised();
    Vector2 v2n = v.normalised();

    return acos(v1n.dotProduct(v2n));
}

float Vector2::dotProduct(const Vector2& v) const
{
    return ((x * v.x) + (y * v.y));
}

Vector2 Vector2::operator + (const Vector2& v) const
{
    return Vector2((x + v.x), (y + v.y));
}

Vector2 Vector2::operator - (const Vector2& v) const
{
    return Vector2((x - v.x), (y - v.y));
}

Vector2 Vector2::operator * (float w) const
{
    return Vector2((x * w), (y * w));
}

Vector2 Vector2::operator / (float w) const
{
    if (w == 0.0f)
        return *this;

    float temp = (1 / w);

    return Vector2((x * temp), (y * temp));
}

float& Vector2::operator [] (unsigned char i)
{
    assert(i < 2);
    return components[i];
}

const float Vector2::operator [] (unsigned char i) const
{
    assert(i < 2);
    return components[i];
}

Vector2& Vector2::Vector2::operator = (const Vector2& v)
{
    x = v.x;
    y = v.y;

    return *this;
}

Vector2& Vector2::Vector2::operator += (const Vector2& v)
{
    x += v.x;
    y += v.y;

    return *this;
}

Vector2& Vector2::Vector2::operator -= (const Vector2& v)
{
    x -= v.x;
    y -= v.y;

    return *this;
}

Vector2& Vector2::Vector2::operator *= (float w)
{
    x *= w;
    y *= w;

    return *this;
}

Vector2& Vector2::Vector2::operator /= (float w)
{
    if (w == 0.0f)
        return *this;

    float temp = 1 / w;

    x *= temp;
    y *= temp;

    return *this;
}

Vector2 Vector2::normalised() const
{
    Vector2 v(*this);

    v.normalize();

    return v;
}

Vector2 Vector2::operator - () const
{
    return Vector2(-x, -y);
}

bool Vector2::operator == (const Vector2& v) const
{
    return ((x == v.x) && (y == v.y));
}

bool Vector2::operator != (const Vector2& v) const
{
    return ((x != v.x) || (y != v.y));
}

std::ostream& operator << (std::ostream& os, const Try::Vector2& v)
{
    os << "Vector2(" << v.x << ", " << v.y << ")";

    return os;
}
