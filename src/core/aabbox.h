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

#ifndef TRY_AABBOX_H
#define TRY_AABBOX_H

#include "core/vector3.h"
#include "core/quaternion.h"

namespace Try
{
    struct AxisAlignedBoundingBox
    {
        Vector3 min;
        Vector3 max;

        AxisAlignedBoundingBox(
            const Vector3& min = Vector3(MaxFloat, MaxFloat, MaxFloat),
            const Vector3& max = Vector3(-MaxFloat, -MaxFloat, -MaxFloat)
        ) : min(min), max(max) {}

        AxisAlignedBoundingBox& join(const AxisAlignedBoundingBox& b)
        {
            if (min == max)
            {
                min = b.min;
                max = b.max;
            }

            else if (b.min != b.max)
            {
                if (b.min.x < min.x) { min.x = b.min.x; }
                if (b.min.y < min.y) { min.y = b.min.y; }
                if (b.min.z < min.z) { min.z = b.min.z; }

                if (b.max.x > max.x) { max.x = b.max.x; }
                if (b.max.y > max.y) { max.y = b.max.y; }
                if (b.max.z > max.z) { max.z = b.max.z; }
            }

            return *this;
        }

        Vector3 size() const
        {
            return max - min;
        }

        Vector3 center() const
        {
            return min + this->size() * 0.5f;
        }
    };
}

#endif // TRY_AABBOX_H
