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

#include <graphics/lightemitter.h>
#include <graphics/graphicsmanager.h>

using namespace Try;

PropertyName LightEmitter::name  = "try.graphics.lightemitter";

MessageName LightEmitter::Msg::radiusChanged = "radiusChanged";
MessageName LightEmitter::Msg::fovChanged = "fovChanged";
MessageName LightEmitter::Msg::colorChanged = "colorChanged";
MessageName LightEmitter::Msg::lightingCtxChanged = "lightingCtxChanged";
MessageName LightEmitter::Msg::shadowCtxChanged = "shadowCtxChanged";

LightEmitter::LightEmitter(Object* owner, const TransformableHandle& light)
    : SceneTransformable(LightEmitter::name, owner, light)
{
    ((Listenable<LightListener>*)graphics)->addListener(this);
}

LightEmitter::LightEmitter(
    Object* owner,
    const String& name,
    float radius,
    float fov,
    const Color& color,
    const ResourceHandle& material,
    const String& lighting_ctx,
    const String& shadow_ctx,
    const Transform& t,
    const TransformableHandle& parent
)
    : SceneTransformable(LightEmitter::name, owner, graphics->loadLight(name, radius, fov, color, material, lighting_ctx, shadow_ctx, t, parent))
{
    ((Listenable<LightListener>*)graphics)->addListener(this);
}

LightEmitter::~LightEmitter()
{
    ((Listenable<LightListener>*)graphics)->removeListener(this);
}

void LightEmitter::setRadius(float radius)
{
    graphics->setLightRadius(m_handle, radius);
}

void LightEmitter::setFOV(float fov)
{
    graphics->setLightFOV(m_handle, fov);
}

void LightEmitter::setColor(const Color& color)
{
    graphics->setLightColor(m_handle, color);
}

void LightEmitter::setLightingContext(const String& ctx)
{
    graphics->setLightLightingContext(m_handle, ctx);
}

void LightEmitter::setShadowContext(const String& ctx)
{
    graphics->setLightShadowContext(m_handle, ctx);
}

float LightEmitter::radius() const
{
    return graphics->lightRadius(m_handle);
}

float LightEmitter::fov() const
{
    return graphics->lightFOV(m_handle);
}

Color LightEmitter::color() const
{
    return graphics->lightColor(m_handle);
}

String LightEmitter::lightingContext() const
{
    return graphics->lightLightingContext(m_handle);
}

String LightEmitter::shadowContext() const
{
    return graphics->lightShadowContext(m_handle);
}


Property* LightEmitter::copy(Object* owner) const
{
    return 0;
}

String LightEmitter::serialize() const
{
    return "";
}

void LightEmitter::onRadiusChanged(float old, float radius)
{
    this->notifyMessage(Message(LightEmitter::Msg::radiusChanged, old, radius));
}

void LightEmitter::onFOVChanged(float old, float fov)
{
    this->notifyMessage(Message(LightEmitter::Msg::fovChanged, old, fov));
}

void LightEmitter::onColorChanged(const Color& old, const Color& color)
{
    this->notifyMessage(Message(LightEmitter::Msg::colorChanged, old, color));
}

void LightEmitter::onLightingCtxChanged(const String& old, const String& ctx)
{
    this->notifyMessage(Message(LightEmitter::Msg::lightingCtxChanged, old, ctx));
}

void LightEmitter::onShadowCtxChanged(const String& old, const String& ctx)
{
    this->notifyMessage(Message(LightEmitter::Msg::shadowCtxChanged, old, ctx));
}
