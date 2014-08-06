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

#ifndef TRY_LIGHTEMITTER_H
#define TRY_LIGHTEMITTER_H

#include <graphics/scenetransformable.h>

namespace Try
{
    class LightEmitter :    public SceneTransformable,
                            protected LightListener
    {
    public:
        static PropertyName name;

        struct Msg
        {
            static MessageName radiusChanged;
            static MessageName fovChanged;
            static MessageName colorChanged;
            static MessageName lightingCtxChanged;
            static MessageName shadowCtxChanged;
        };

    public:
        LightEmitter(
            Object* owner,
            const TransformableHandle& light
        );

        LightEmitter(
            Object* owner,
            const String& name,
            float radius = 200.0f,
            float fov = 90.0f,
            const Color& color = Color(),
            const ResourceHandle& material = 0,
            const String& lighting_ctx = TRY_LIGHT_DEFAULT_LIGHTING_CTX,
            const String& shadow_ctx = TRY_LIGHT_DEFAULT_SHADOW_CTX,
            const Transform& t = Transform(),
            const TransformableHandle& parent = TransformableRoot
        );

        virtual ~LightEmitter();

        void setRadius(float radius);
        void setFOV(float fov);
        void setColor(const Color& color);
        void setLightingContext(const String& ctx);
        void setShadowContext(const String& ctx);

        float radius() const;
        float fov() const;
        Color color() const;
        String lightingContext() const;
        String shadowContext() const;

        Property* copy(Object* owner) const;

        String serialize() const;

    protected:
        void onRadiusChanged(float old, float radius);
        void onFOVChanged(float old, float fov);
        void onColorChanged(const Color& old, const Color& color);
        void onLightingCtxChanged(const String& old, const String& ctx);
        void onShadowCtxChanged(const String& old, const String& ctx);
    };
}

#endif // TRY_LIGHTEMITTER_H
