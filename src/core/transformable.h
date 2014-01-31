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

#ifndef TRY_TRANSFORMABLE_H
#define TRY_TRANSFORMABLE_H

#include "aabbox.h"

namespace Try
{
    struct Transform
    {
        Vector3 position;
        Quaternion rotation;
        Vector3 scale;

        Transform(
                const Vector3& pos = Vector3::Zero,
                const Quaternion& rot = Quaternion::Identity,
                const Vector3& scale = Vector3::Identity
                ) : position(pos), rotation(rot), scale(scale)
        {
        }

        bool operator==(const Transform& t) const
        {
            if (position != t.position)
                return false;

            if (rotation != t.rotation)
                return false;

            if (scale != t.scale)
                return false;

            return true;
        }

        bool operator!=(const Transform& t) const
        {
            return !(*this == t);
        }
    };

    class Transformable
    {
    public:
        virtual ~Transformable() {}

        virtual void setTransform(const Transform& transform) = 0;
        virtual Transform transform() const = 0;
        virtual AxisAlignedBoundingBox worldAABB() const = 0;

        void setTransformComponents(const Vector3& pos, const Vector3& rot, const Vector3& scale) { this->setTransform(Transform(pos, Quaternion(rot), scale)); }
        void setPosition(const Vector3& pos) { this->setTransform(Transform(pos, this->rotation(), this->scale())); }
        void setRotation(const Quaternion& rot) { this->setTransform(Transform(this->position(), rot, this->scale())); }
        void setRotation(const Vector3& rot) { this->setTransformComponents(this->position(), rot, this->scale()); }
        void setScale(const Vector3& scale) { this->setTransform(Transform(this->position(), this->rotation(), scale)); }
        void resetTransform() { this->setTransform(Transform(Vector3::Identity, Quaternion::Identity, Vector3::Identity)); }

        void translate(const Vector3& dp) { this->setPosition(this->position() + dp); }
        void rotate(const Quaternion& dr) { this->setRotation(this->rotation() * dr); }
        void rotate(const Vector3& dr) { this->rotate(Quaternion(dr)); }
        void resize(const Vector3& ds) { this->setScale(this->scale() + ds); }

        void lookAt(const Vector3& target, const Vector3& up = Vector3::YAxis)
        {
            // FIXME: is it correct?

            Transform t = this->transform();
            Vector3 diff = t.position - target;
            Vector3 rot;

            if (diff.y != 0)
                rot.x = atan2f(diff.y, sqrtf(diff.x*diff.x + diff.z*diff.z));

            if (diff.z != 0 )
                rot.y = atan2(diff.x, diff.z);
            else if (diff.x < 0)
                rot.y = -Try::HalfPi;
            else
                rot.y = Try::HalfPi;

            // Convert from radians to degrees.
            rot *= Try::RadToDeg;

            this->setRotation(rot);
        }

        Vector3 position() const { return this->transform().position; }
        Quaternion rotation() const { return this->transform().rotation; }
        Vector3 scale() const { return this->transform().scale; }
    };
}

#endif // TRY_TRANSFORMABLE_H
