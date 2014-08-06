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

#ifndef TRY_CAMERACONTROLLER_H
#define TRY_CAMERACONTROLLER_H

#include <graphics/scenetransformable.h>

namespace Try
{
    class CameraController :    public SceneTransformable,
                                protected CameraListener
    {
    public:
        static PropertyName name;

        struct Msg
        {
            static MessageName viewportChanged;
        };

    public:
        CameraController(
            Object* owner,
            const TransformableHandle& camera
        );

        CameraController(
            Object* owner,
            const String& name,
            const ResourceHandle& pipeline,
            int width,
            int height,
            float fov = 45.0f,
            float near_clip = 0.1f,
            float far_clip = 1000.0f,
            const Transform& t = Transform(),
            const TransformableHandle& parent = TransformableRoot
        );

        CameraController(
            Object* owner,
            const String& name,
            const String& pipeline_filename,
            int width,
            int height,
            float fov = 45.0f,
            float near_clip = 0.1f,
            float far_clip = 1000.0f,
            const Transform& t = Transform(),
            const TransformableHandle& parent = TransformableRoot
        );

        virtual ~CameraController();

        void setViewport(int width, int height, float fov, float near_clip, float far_clip);

        int viewportWidth() const;
        int viewportHeight() const;
        float viewportFOV() const;
        float viewportNearClip() const;
        float viewportFarClip() const;

        Vector3 projectToWorld(float nx, float ny) const;
        TransformableHandle pick(float nx, float ny) const;
        Property* copy(Object* owner) const;
        String serialize() const;

    protected:
        void onViewportChanged(int width, int height, float fov, float near_clip, float far_clip);
    };
}

#endif // TRY_CAMERACONTROLLER_H
