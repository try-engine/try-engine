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

#ifndef TRY_SCENETRANSFORMABLE_H
#define TRY_SCENETRANSFORMABLE_H

#include <graphics/base.h>
#include <core/property.h>
#include <list>

namespace Try
{
    class SceneTransformable :  public Property,
                                public Transformable,
                                protected SceneTransformableListener
    {
    public:
        struct Msg
        {
            static MessageName handleChanged;
            static MessageName parentChanged;
            static MessageName transformChanged;
            static MessageName flagsChanged;
        };

    protected:
        TransformableHandle m_handle;

        static std::list<SceneTransformable*> s_cache;

    public:
        virtual ~SceneTransformable();

        void setHandle(const TransformableHandle& handle);
        void setParentHandle(const TransformableHandle& parent);
        void setTransform(const Transform& t);

        TransformableHandle handle() const;
        TransformableHandle parentHandle() const;
        String handleName() const;
        Transform transform() const;
        AxisAlignedBoundingBox worldAABB() const;

        static std::vector<SceneTransformable*> query(const TransformableHandle& handle);

    protected:
        SceneTransformable(const String& name, Object* owner, const TransformableHandle& handle);

        void onParentChanged(const TransformableHandle& old, const TransformableHandle& parent);
        void onTransformChanged(const Transform& old, const Transform& t);
        void onFlagsChanged(int old, int flags);
        void onRemoved();
    };
}

#endif // TRY_SCENETRANSFORMABLE_H
