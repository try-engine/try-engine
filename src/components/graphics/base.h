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

#ifndef TRY_GRAPHICS_BASE_H
#define TRY_GRAPHICS_BASE_H

#include <core/try.h>

#define TRY_LIGHT_DEFAULT_LIGHTING_CTX "LIGHTING"
#define TRY_LIGHT_DEFAULT_SHADOW_CTX "SHADOWMAP"

namespace Try
{
    typedef int ResourceHandle;
    typedef int TransformableHandle;

    const TransformableHandle TransformableRoot = 1;

    struct Color
    {
        float r, g, b, a;

        Color(float r = 1, float g = 1, float b = 1, float a = 1)
            : r(r), g(g), b(b), a(a) {}

        bool operator==(const Color& c) const
        {
            return (c.r == r && c.g == g && c.b == b && c.a == a);
        }

        bool operator!=(const Color& c) const
        {
            return !(*this == c);
        }
    };

    namespace Colors
    {
        const Color White = Color(1, 1, 1);
        const Color Black = Color(0, 0, 0);
        const Color Gray = Color(0.5, 0.5, 0.5);
        const Color Red = Color(1, 0, 0);
        const Color Green = Color(0, 1, 0);
        const Color Blue = Color(0, 0, 1);
        const Color Yellow = Color(1, 1, 0);
        const Color Purple = Color(1, 0, 1);
    }

    struct VertexDef
    {
        Vector3 pos;
        Color color;
        Vector2 texCoords;
        ResourceHandle texture;

        VertexDef(
            const Vector3& pos,
            const Color& color = Try::Colors::White,
            const Vector2& tex_coords = Vector2::Zero,
            const ResourceHandle& tex = 0
        )
            : pos(pos), color(color), texCoords(tex_coords), texture(tex) {}
    };

    typedef std::vector<VertexDef> VertexList;
    typedef std::vector<unsigned int> IndexList;

    class SceneTransformableListener
    {
    public:
        virtual TransformableHandle handle() const = 0;

        virtual void onParentChanged(const TransformableHandle& old, const TransformableHandle& parent) {}
        virtual void onTransformChanged(const Transform& old, const Transform& t) {}
        virtual void onFlagsChanged(int old, int flags) {}
        virtual void onRemoved() {}
    };

    class CameraListener
    {
    public:
        virtual void onViewportChanged(int width, int height, float fov, float near_clip, float far_clip) {}
    };

    class LightListener
    {
    public:
        virtual void onRadiusChanged(float old, float radius) {}
        virtual void onFOVChanged(float old, float fov) {}
        virtual void onColorChanged(const Color& old, const Color& color) {}
        virtual void onLightingCtxChanged(const String& old, const String& ctx) {}
        virtual void onShadowCtxChanged(const String& old, const String& ctx) {}
    };

    class RenderContext;
    class RenderWindow;

    class RenderListener
    {
    public:
        virtual void onRenderStarted(double dt) {}
        virtual void onRenderStarted(RenderContext* rc, double dt) {}
        virtual void onRenderEnded(RenderContext* rc) {}
        virtual void onRenderEnded() {}
    };

    class RenderContextListener
    {
    public:
        virtual void onContextActivated(RenderContext* rc) {}
        virtual void onContextUpdated(RenderContext* rc) {}
        virtual void onCameraChanged(RenderContext* rc, const TransformableHandle& t) {}
    };

    class RenderWindowListener
    {
    public:
        virtual void onWindowResized(RenderWindow* rw, int width, int height) {}
        virtual void onWindowClosed(RenderWindow* rw, int ret_code) {}
    };
}

#endif // TRY_GRAPHICS_BASE_H
