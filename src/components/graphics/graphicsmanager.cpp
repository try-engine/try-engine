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

#include <graphics/graphicsmanager.h>
#include <core/logger.h>
#include <Horde3DUtils.h>
#include <Horde3D.h>
#include <GL/gl.h>

using namespace Try;

GraphicsManager::GraphicsManager(RenderContext* rc)
{
    this->registerRenderContext(rc);

    h3dInit();

    h3dSetOption(H3DOptions::LoadTextures, 1);
    h3dSetOption(H3DOptions::TexCompression, 0);
    h3dSetOption(H3DOptions::FastAnimation, 0);
    h3dSetOption(H3DOptions::MaxAnisotropy, 4);
    h3dSetOption(H3DOptions::ShadowMapSize, 2048);

    logger->log("Graphics: init.");
}

GraphicsManager::~GraphicsManager()
{
    int size = m_renderContexts.size();
    for (int i=size; i>0; i--)
        delete m_renderContexts.at(i-1);

    h3dRelease();

    logger->log("Graphics: released.");
}

void GraphicsManager::registerRenderContext(RenderContext* rc)
{
    if (rc && !this->hasRenderContext(rc))
        m_renderContexts.push_back(rc);
}

void GraphicsManager::unregisterRenderContext(RenderContext* rc)
{
    if (rc)
    {
        for (int i=0; i<m_renderContexts.size(); i++)
        {
            if (m_renderContexts.at(i) == rc)
            {
                m_renderContexts.erase(m_renderContexts.begin() + i);
                break;
            }
        }
    }
}

void GraphicsManager::renderOneFrame(double dt)
{
    std::vector<RenderListener*> listeners = ((Listenable<RenderListener>*)this)->listeners();

    for (int i=0; i<listeners.size(); ++i)
        listeners.at(i)->onRenderStarted(dt);

    this->renderOnContexts(dt);

    this->finalizeRender();

    for (int i=0; i<listeners.size(); ++i)
        listeners.at(i)->onRenderEnded();
}

int GraphicsManager::renderContextCount() const
{
    return m_renderContexts.size();
}

RenderContext* GraphicsManager::renderContext(int index) const
{
    if (index < this->renderContextCount())
        return m_renderContexts.at(index);

    return 0;
}

bool GraphicsManager::hasRenderContext(RenderContext* rc) const
{
    if (rc)
    {
        for (int i=0; i<m_renderContexts.size(); i++)
            if (m_renderContexts.at(i) == rc)
                return true;
    }

    return false;
}

void GraphicsManager::removeResource(const ResourceHandle& res)
{
    h3dRemoveResource(res);
}

ResourceHandle GraphicsManager::createTexture(const String &name, const unsigned char* data, const Vector2& size)
{
    H3DRes res = h3dCreateTexture(name.c_str(), size.x, size.y, H3DFormats::TEX_BGRA8, H3DResFlags::TexDynamic);

    unsigned char* data_src = static_cast<unsigned char*>(h3dMapResStream(res, H3DTexRes::ImageElem, 0, H3DTexRes::ImgPixelStream, false, true ));

    int rowsize = size.y*4;

    for (int row=0; row<size.x; ++row)
    {
        int rk = row*rowsize;

        unsigned char* row_ptr = data_src + rk;

        for (int col=0; col<size.y; ++col)
        {
            int ck = col*4;

            unsigned char* sample = row_ptr + ck;

            sample[0] = data[rk+ck+2];
            sample[1] = data[rk+ck+1];
            sample[2] = data[rk+ck+0];
            sample[3] = data[rk+ck+3];
        }
    }

    h3dUnmapResStream(res);

    h3dutLoadResourcesFromDisk("data/");

    return res;
}

ResourceHandle GraphicsManager::loadTexture(const String& filename)
{
    ResourceHandle tex_res = h3dAddResource(H3DResTypes::Texture, filename.c_str(), 0);

    h3dutLoadResourcesFromDisk("data/");

    return tex_res;
}

Vector2 GraphicsManager::textureSize(const ResourceHandle& res) const
{
    int w = h3dGetResParamI(res, H3DTexRes::ImageElem, 0, H3DTexRes::ImgWidthI);
    int h = h3dGetResParamI(res, H3DTexRes::ImageElem, 0, H3DTexRes::ImgHeightI);

    return Vector2(w, h);
}

ResourceHandle GraphicsManager::createGeometry(
    const String& name,
    const VertexList& vertices,
    const IndexList& indices)
{
    std::vector<float> pos;
    std::vector<float> uv;

    for (int v=0; v<vertices.size(); ++v)
    {
        VertexDef vertex = vertices.at(v);

        pos.push_back(vertex.pos.x);
        pos.push_back(vertex.pos.y);
        pos.push_back(vertex.pos.z);
        uv.push_back(vertex.texCoords.x);
        uv.push_back(vertex.texCoords.y);
    }

    ResourceHandle res = h3dutCreateGeometryRes(name.c_str(), vertices.size(), indices.size(), pos.data(), (unsigned int*)indices.data(), 0, 0, 0, uv.data(), 0);

    h3dutLoadResourcesFromDisk("data/");

    return res;
}

ResourceHandle GraphicsManager::loadAnimation(
    const TransformableHandle& handle,
    const String& filename,
    float weight,
    int layer
)
{
    ResourceHandle anim_res = h3dAddResource(H3DResTypes::Animation, filename.c_str(), 0);

    h3dutLoadResourcesFromDisk("data/");

    return this->loadAnimation(handle, anim_res, weight, layer);
}

ResourceHandle GraphicsManager::loadAnimation(
    const TransformableHandle& handle,
    const ResourceHandle& anim_res,
    float weight,
    int layer
)
{
    int stage = this->animationCount(handle);

    h3dSetupModelAnimStage(handle, stage, anim_res, layer, "", false);
    h3dSetModelAnimParams(handle, stage, 0, weight);

    return anim_res;
}

void GraphicsManager::changeAnimationWeight(const TransformableHandle& handle, int animation_id, float weight)
{
    h3dSetModelAnimParams(handle, animation_id, this->animationTime(handle, animation_id), weight);
}

void GraphicsManager::updateAnimation(const TransformableHandle& handle, int animation_id, float dt)
{
    float prev_time;
    float weight;
    int count = this->animationCount(handle);

    h3dGetModelAnimParams(handle, animation_id, &prev_time, &weight);
    h3dSetModelAnimParams(handle, animation_id, prev_time + dt, weight);
    h3dUpdateModel(handle, H3DModelUpdateFlags::Animation | H3DModelUpdateFlags::Geometry);
}

void GraphicsManager::resetAnimation(const TransformableHandle& handle, int animation_id)
{
    h3dSetModelAnimParams(handle, animation_id, 0, this->animationWeight(handle, animation_id));
}

int GraphicsManager::animationCount(const TransformableHandle& handle) const
{
    return h3dGetNodeParamI(handle, H3DModel::AnimCountI);
}

float GraphicsManager::animationTime(const TransformableHandle& handle, int animation_id) const
{
    float time;

    h3dGetModelAnimParams(handle, animation_id, &time, 0);

    return time;
}

float GraphicsManager::animationWeight(const TransformableHandle& handle, int animation_id) const
{
    float weight;

    h3dGetModelAnimParams(handle, animation_id, 0, &weight);

    return weight;
}

void GraphicsManager::setParent(const TransformableHandle& handle, const TransformableHandle& parent)
{
    TransformableHandle old = this->parent(handle);

    if (old != parent)
    {
        h3dSetNodeParent(handle, parent);

        std::vector<SceneTransformableListener*> listeners = ((Listenable<SceneTransformableListener>*)this)->listeners();
        for (int i=0; i<listeners.size(); i++)
        {
            SceneTransformableListener* listener = listeners.at(i);
            if (listener && listener->handle() == handle)
                listener->onParentChanged(old, parent);
        }
    }
}

void GraphicsManager::setFlag(const TransformableHandle& handle, TransformableFlags flag, bool value)
{
    int flags = this->flags(handle);

    if (value)
        flags |= flag;
    else
        flags &= ~flag;

    this->setFlags(handle, flags);
}

void GraphicsManager::setFlags(const TransformableHandle& handle, int flags)
{
    int old = this->flags(handle);

    if (old != flags)
    {
        h3dSetNodeFlags(handle, flags, true);

        std::vector<SceneTransformableListener*> listeners = ((Listenable<SceneTransformableListener>*)this)->listeners();
        for (int i=0; i<listeners.size(); i++)
        {
            SceneTransformableListener* listener = listeners.at(i);
            if (listener && listener->handle() == handle)
                listener->onFlagsChanged(old, flags);
        }
    }
}

void GraphicsManager::setTransform(const TransformableHandle& handle, const Transform& t)
{
    this->setTransform(handle, t.position, t.rotation.toEulerAngle(), t.scale);
}

void GraphicsManager::setTransform(
    const TransformableHandle& handle,
    const Vector3& pos,
    const Vector3& rot,
    const Vector3& scale
)
{
    Transform old = this->transform(handle);
    Transform t(pos, Quaternion(rot), scale);

    if (old != t)
    {
        h3dSetNodeTransform(handle, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, scale.x, scale.y, scale.z);

        std::vector<SceneTransformableListener*> listeners = ((Listenable<SceneTransformableListener>*)this)->listeners();
        for (int i=0; i<listeners.size(); i++)
        {
            SceneTransformableListener* listener = listeners.at(i);
            if (listener && listener->handle() == handle)
                listener->onTransformChanged(old, t);
        }
    }
}

void GraphicsManager::remove(const TransformableHandle& handle)
{
    h3dRemoveNode(handle);

    h3dReleaseUnusedResources();

    std::vector<SceneTransformableListener*> listeners = ((Listenable<SceneTransformableListener>*)this)->listeners();
    for (int i=0; i<listeners.size(); i++)
    {
        SceneTransformableListener* listener = listeners.at(i);
        if (listener && listener->handle() == handle)
            listener->onRemoved();
    }
}

String GraphicsManager::name(const TransformableHandle& handle) const
{
    return h3dGetNodeParamStr(handle, H3DNodeParams::NameStr);
}

int GraphicsManager::flags(const TransformableHandle& handle) const
{
    return h3dGetNodeFlags(handle);
}

Transform GraphicsManager::transform(const TransformableHandle& handle) const
{
    Transform t;
    Vector3 rot;

    h3dGetNodeTransform(handle, &t.position.x, &t.position.y, &t.position.z, &rot.x, &rot.y, &rot.z, &t.scale.x, &t.scale.y, &t.scale.z);

    t.rotation = Quaternion(rot);

    return t;
}

TransformableHandle GraphicsManager::parent(const TransformableHandle& handle) const
{
    return h3dGetNodeParent(handle);
}

AxisAlignedBoundingBox GraphicsManager::worldAABB(const TransformableHandle& handle) const
{
    AxisAlignedBoundingBox aabb;

    h3dGetNodeAABB(handle, &aabb.min.x, &aabb.min.y, &aabb.min.z, &aabb.max.x, &aabb.max.y, &aabb.max.z);

    return aabb;
}

TransformableHandle GraphicsManager::loadModel(
    const String& name,
    const ResourceHandle& model_res,
    const Transform& t,
    const TransformableHandle& parent
)
{
    TransformableHandle n = h3dAddModelNode(parent, name.c_str(), model_res);

    this->setParent(n, parent);
    this->setTransform(n, t);

    return n;

}

TransformableHandle GraphicsManager::loadModel(
    const String& filename,
    const Transform& t,
    const TransformableHandle& parent
)
{
    H3DRes res = h3dAddResource(H3DResTypes::SceneGraph, filename.c_str(), 0);

    h3dutLoadResourcesFromDisk("data/");

    TransformableHandle n = h3dAddNodes(parent, res);

    this->setParent(n, parent);
    this->setTransform(n, t);

    return n;

}

TransformableHandle GraphicsManager::loadParticles(
    const String& name,
    const ResourceHandle& material,
    const ResourceHandle& effect,
    int max_particles,
    int respawn_count,
    const Transform& t,
    const TransformableHandle& parent
)
{
    TransformableHandle p = h3dAddEmitterNode(parent, name.c_str(), material, effect, max_particles, respawn_count);

    this->setTransform(p, t);

    return p;
}

TransformableHandle GraphicsManager::loadParticles(
    const String& filename,
    const Transform& t,
    const TransformableHandle& parent
)
{
    ResourceHandle res = h3dAddResource(H3DResTypes::SceneGraph, filename.c_str(), 0);

    h3dutLoadResourcesFromDisk("data/");

    TransformableHandle p = h3dAddNodes(parent, res);

    this->setTransform(p, t);

    return p;
}

void GraphicsManager::updateParticles(const TransformableHandle& handle, float dt)
{
    h3dUpdateEmitter(handle, dt);
}

TransformableHandle GraphicsManager::loadCamera(
    const String& name,
    const ResourceHandle& pipeline,
    int width,
    int height,
    float fov,
    float near_clip,
    float far_clip,
    const Transform& t,
    const TransformableHandle& parent
)
{
    TransformableHandle c = h3dAddCameraNode(parent, name.c_str(), pipeline);

    this->setupCameraViewport(c, width, height, fov, near_clip, far_clip);
    this->setTransform(c, t);

    return c;
}

TransformableHandle GraphicsManager::loadCamera(
    const String& name,
    const String& pipeline_filename,
    int width,
    int height,
    float fov,
    float near_clip,
    float far_clip,
    const Transform& t,
    const TransformableHandle& parent
)
{
    ResourceHandle pipeline = h3dAddResource(H3DResTypes::Pipeline, pipeline_filename.c_str(), 0);

    h3dutLoadResourcesFromDisk("data/");

    return this->loadCamera(name, pipeline, width, height, fov, near_clip, far_clip, t, parent);
}

void GraphicsManager::setupCameraViewport(const TransformableHandle& cam, int width, int height, float fov, float near_clip, float far_clip)
{
    if (width != this->cameraViewportWidth(cam)
        || height != this->cameraViewportHeight(cam)
        || fov != this->cameraViewportFOV(cam)
        || near_clip != this->cameraViewportNearClip(cam)
        || far_clip != this->cameraViewportFarClip(cam))
    {
        h3dSetNodeParamI(cam, H3DCamera::ViewportXI, 0);
        h3dSetNodeParamI(cam, H3DCamera::ViewportYI, 0);
        h3dSetNodeParamI(cam, H3DCamera::ViewportWidthI, width);
        h3dSetNodeParamI(cam, H3DCamera::ViewportHeightI, height);

        float aratio = (float)width/height;
        ResourceHandle pipeline = h3dGetNodeParamI(cam, H3DCamera::PipeResI);

        h3dSetupCameraView(cam, fov, aratio, near_clip, far_clip);

        h3dResizePipelineBuffers(pipeline, width, height);

        // TODO: only registered handle.
        std::vector<CameraListener*> listeners = ((Listenable<CameraListener>*)this)->listeners();
        for (int i=0; i<listeners.size(); i++)
            listeners.at(i)->onViewportChanged(width, height, fov, near_clip, far_clip);
    }
}

int GraphicsManager::cameraViewportWidth(const TransformableHandle& cam) const
{
    return h3dGetNodeParamI(cam, H3DCamera::ViewportWidthI);
}

int GraphicsManager::cameraViewportHeight(const TransformableHandle& cam) const
{
    return h3dGetNodeParamI(cam, H3DCamera::ViewportHeightI);
}

float GraphicsManager::cameraViewportFOV(const TransformableHandle& cam) const
{
    float ymax = h3dGetNodeParamF(cam, H3DCamera::TopPlaneF, 0);
    float near = h3dGetNodeParamF(cam, H3DCamera::NearPlaneF, 0);

    // NOTE: ymax = near * tanf( degToRad( fov / 2 ) );

    return (atanf(ymax / near) * Try::RadToDeg * 2);
}

float GraphicsManager::cameraViewportNearClip(const TransformableHandle& cam) const
{
    return h3dGetNodeParamF(cam, H3DCamera::NearPlaneF, 0);
}

float GraphicsManager::cameraViewportFarClip(const TransformableHandle& cam) const
{
    return h3dGetNodeParamF(cam, H3DCamera::FarPlaneF, 0);
}

Vector3 GraphicsManager::projectFromCameraToWorld(const TransformableHandle& cam, float nx, float ny) const
{
    Vector3 p;
    Vector3 d;

    h3dutPickRay(cam, nx, ny, &p.x, &p.y, &p.z, &d.x, &d.y, &d.z);

    return d;
}

Vector3 GraphicsManager::projectFromCameraToWorld(const TransformableHandle& cam, float nx, float ny, float clip) const
{
    float old = this->cameraViewportFarClip(cam);

    h3dSetNodeParamF(cam, H3DCamera::FarPlaneF, 0, clip);

    Vector3 r = this->projectFromCameraToWorld(cam, nx, ny);

    h3dSetNodeParamF(cam, H3DCamera::FarPlaneF, 0, old);

    return r;
}

TransformableHandle GraphicsManager::pickFromCamera(const TransformableHandle& cam, float nx, float ny) const
{
    TransformableHandle picked = h3dutPickNode(cam, nx, ny);

    if (h3dGetNodeType(picked) == H3DNodeTypes::Mesh)
        return this->parent(picked);

    return picked;
}

TransformableHandle GraphicsManager::loadLight(
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
{
    TransformableHandle n = h3dAddLightNode(parent, name.c_str(), material, lighting_ctx.c_str(), shadow_ctx.c_str());

    // FIXME: hard-coded params.
    h3dSetNodeParamI(n, H3DLight::ShadowMapCountI, 3 );
    h3dSetNodeParamF(n, H3DLight::ShadowSplitLambdaF, 0, 0.9f );
    h3dSetNodeParamF(n, H3DLight::ShadowMapBiasF, 0, 0.001f );

    this->setLightRadius(n, radius);
    this->setLightFOV(n, fov);

    return n;
}

void GraphicsManager::setLightRadius(const TransformableHandle& light, float radius)
{
    float old = this->lightRadius(light);

    if (old != radius)
    {
        h3dSetNodeParamF(light, H3DLight::RadiusF, 0, radius);

        // TODO: only registered handle.
        std::vector<LightListener*> listeners = ((Listenable<LightListener>*)this)->listeners();
        for (int i=0; i<listeners.size(); i++)
            listeners.at(i)->onRadiusChanged(old, radius);
    }
}

void GraphicsManager::setLightFOV(const TransformableHandle& light, float fov)
{
    float old = this->lightFOV(light);

    if (old != fov)
    {
        h3dSetNodeParamF(light, H3DLight::FovF, 0, fov);

        // TODO: only registered handle.
        std::vector<LightListener*> listeners = ((Listenable<LightListener>*)this)->listeners();
        for (int i=0; i<listeners.size(); i++)
            listeners.at(i)->onFOVChanged(old, fov);
    }
}

void GraphicsManager::setLightColor(const TransformableHandle& light, const Color& c)
{
    Color old = this->lightColor(light);

    if (old != c)
    {
        h3dSetNodeParamF(light, H3DLight::ColorF3, 0, c.r);
        h3dSetNodeParamF(light, H3DLight::ColorF3, 1, c.g);
        h3dSetNodeParamF(light, H3DLight::ColorF3, 2, c.b);

        // TODO: only registered handle.
        std::vector<LightListener*> listeners = ((Listenable<LightListener>*)this)->listeners();
        for (int i=0; i<listeners.size(); i++)
            listeners.at(i)->onColorChanged(old, c);
    }
}

void GraphicsManager::setLightLightingContext(const TransformableHandle& light, const String& ctx)
{
    String old = this->lightLightingContext(light);

    if (old != ctx)
    {
        h3dSetNodeParamStr(light, H3DLight::LightingContextStr, ctx.c_str());

        // TODO: only registered handle.
        std::vector<LightListener*> listeners = ((Listenable<LightListener>*)this)->listeners();
        for (int i=0; i<listeners.size(); i++)
            listeners.at(i)->onLightingCtxChanged(old, ctx);
    }
}

void GraphicsManager::setLightShadowContext(const TransformableHandle& light, const String& ctx)
{
    String old = this->lightShadowContext(light);

    if (old != ctx)
    {
        h3dSetNodeParamStr(light, H3DLight::ShadowContextStr, ctx.c_str());

        // TODO: only registered handle.
        std::vector<LightListener*> listeners = ((Listenable<LightListener>*)this)->listeners();
        for (int i=0; i<listeners.size(); i++)
            listeners.at(i)->onShadowCtxChanged(old, ctx);
    }
}

float GraphicsManager::lightRadius(const TransformableHandle& light) const
{
    return h3dGetNodeParamF(light, H3DLight::RadiusF, 0);
}

float GraphicsManager::lightFOV(const TransformableHandle& light) const
{
    return h3dGetNodeParamF(light, H3DLight::FovF, 0);
}

Color GraphicsManager::lightColor(const TransformableHandle& light) const
{
    return Color(
        h3dGetNodeParamF(light, H3DLight::ColorF3, 0),
        h3dGetNodeParamF(light, H3DLight::ColorF3, 1),
        h3dGetNodeParamF(light, H3DLight::ColorF3, 2)
    );
}

String GraphicsManager::lightLightingContext(const TransformableHandle& light) const
{
    return h3dGetNodeParamStr(light, H3DLight::LightingContextStr);
}

String GraphicsManager::lightShadowContext(const TransformableHandle& light) const
{
    return h3dGetNodeParamStr(light, H3DLight::ShadowContextStr);
}

void GraphicsManager::drawLine(const Vector3& start, const Vector3& end, const Color& color)
{
    int index = m_vertices.size();

    this->addVertex(start, color);
    this->addVertex(end, color);

    this->addLineIndices(index, index+1);
}

void GraphicsManager::drawCircle(const Vector3& center, float radius, int segment_count, const Color& color)
{
    if (segment_count > 0)
    {
        float increment = TwoPi / segment_count;
        float angle = 0.0f;
        int index = m_vertices.size();

        for (int i = 0; i < segment_count; i++)
        {
            Vector3 vertex(center.x + radius * cos(angle), center.y, center.z + radius * sin(angle));

            this->addVertex(vertex, color);

            angle += increment;
        }

        for (int i = 0; i < segment_count; i++)
            this->addLineIndices(index + i, index + i + 1 < segment_count ? index + i + 1 : index);
    }
}

void GraphicsManager::drawQuad(const Vector3& center, float width, float height, const Color& color)
{
    int index = m_vertices.size();

    float x = width * 0.5;
    float y = height * 0.5;

    this->addVertex(center + Vector3(-x, 0, -y), color);
    this->addVertex(center + Vector3( x, 0, -y), color);
    this->addVertex(center + Vector3( x, 0,  y), color);
    this->addVertex(center + Vector3(-x, 0,  y), color);

    this->addLineIndices(index    , index + 1);
    this->addLineIndices(index + 1, index + 2);
    this->addLineIndices(index + 2, index + 3);
    this->addLineIndices(index + 3, index    );
}

void GraphicsManager::drawGrid(const Vector3& center, const Color& color, float cell_size, int numcols, int numrows)
{
    float width = numcols * cell_size;
    float height = numrows * cell_size;

    for (int i = 0; i < numrows; ++i)
    {
        Vector3 s = center +  Vector3(-width/2, 0, cell_size * i - height/2);
        Vector3 e = center +  Vector3(+width/2, 0, cell_size * i - height/2);

        this->drawLine(s, e, color);
    }

    for (int i = 0; i < numcols; ++i)
    {
        Vector3 s = center +  Vector3(cell_size * i - width/2, 0, -height/2);
        Vector3 e = center +  Vector3(cell_size * i - width/2, 0, +height/2);

        this->drawLine(s, e, color);
    }

    this->drawQuad(center, width, height, color);
}

void GraphicsManager::drawBox(const Vector3& center, const Vector3& size, const Color& color)
{
    if (size.y > 0)
    {
        float y = size.y * 0.5;

        int index = m_vertices.size();

        this->drawQuad(Vector3(center.x, center.y-y, center.z), size.x, size.z, color);
        this->drawQuad(Vector3(center.x, center.y+y, center.z), size.x, size.z, color);

        this->addLineIndices(index    , index + 4);
        this->addLineIndices(index + 1, index + 5);
        this->addLineIndices(index + 2, index + 6);
        this->addLineIndices(index + 3, index + 7);
    }
    else
    {
        this->drawQuad(center, size.x, size.z, color);
    }
}

void GraphicsManager::drawCone(const Vector3& center, float radius, float length, int segment_count, const Color& color)
{
    int index = m_vertices.size();

    this->drawCircle(center + Vector3(0, -length/2, 0), radius, segment_count, color);

    this->addVertex(center + Vector3(0, +length/2, 0), color);

    for (int i=0; i<segment_count; i++)
        this->addLineIndices(index + i, index + segment_count);
}

void GraphicsManager::drawCylinder(const Vector3& center, float radius, float length, int segment_count, const Color& color)
{
    int index = m_vertices.size();

    this->drawCircle(center + Vector3(0, -length*0.5, 0), radius, segment_count, color);
    this->drawCircle(center + Vector3(0, +length*0.5, 0), radius, segment_count, color);

    for (int i=0; i<segment_count; i++)
        this->addLineIndices(index + i, index + segment_count + i);
}

void GraphicsManager::drawGeometry(const Vector3& center, const VertexList& vertices, const IndexList& indices, const ResourceHandle& texture)
{
    if (indices.size() % 3 == 0)
    {
        int index = m_vertices.size();

        for (int v=0; v<vertices.size(); ++v)
        {
            VertexDef vertex = vertices.at(v);
            vertex.pos += center;

            m_vertices.push_back(vertex);
        }

        for (int i=0; i<indices.size(); ++i)
            m_triIndices.push_back(index + indices.at(i));
    }
}

void GraphicsManager::renderOnContexts(float dt)
{
    for (int i=0; i<this->renderContextCount(); i++)
    {
        RenderContext* rc = m_renderContexts.at(i);

        if (rc)
        {
            rc->activateContext();

            TransformableHandle cam = rc->activeCamera();

            if (cam)
            {
                std::vector<RenderListener*> listeners = ((Listenable<RenderListener>*)this)->listeners();
                int size = listeners.size();

                // Render started on this context.
                for (int i=0; i<size; ++i)
                    listeners.at(i)->onRenderStarted(rc, dt);

                // 1. Render Horde3D stuff.
                h3dRender(cam);

                // 2. Render native OpenGL primitives.
                this->renderRawGeometries(cam);

                // Render ended on this context.
                for (int i=0; i<size; ++i)
                    listeners.at(i)->onRenderEnded(rc);
            }

            rc->updateContext();
        }
    }
}

void GraphicsManager::renderRawGeometries(const TransformableHandle& cam)
{
    if (cam && m_vertices.size() > 0)
    {
        const float* t = 0;
        h3dGetNodeTransMats(cam, 0, &t);

        if (!t) return;

        Matrix4 trans_mat;
        memcpy(trans_mat.components, t, 16*sizeof(float));

        Matrix4 proj_mat;
        h3dGetCameraProjMat(cam, proj_mat.components);

        // Save OpenGL states.
        glPushAttrib(GL_ALL_ATTRIB_BITS);

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(proj_mat.components);

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(trans_mat.invert().components);

        glLineWidth(1.0);

        // Draw trinagles.
        /**/
        glBegin(GL_TRIANGLES);

        for (int i=0; i<m_triIndices.size(); i += 3)
        {
            int i1 = m_triIndices.at(i);
            int i2 = m_triIndices.at(i+1);
            int i3 = m_triIndices.at(i+2);

            VertexDef v1 = m_vertices.at(i1);
            VertexDef v2 = m_vertices.at(i2);
            VertexDef v3 = m_vertices.at(i3);

            std::cout << "V1: " << v1.pos << std::endl;
            std::cout << "V2: " << v2.pos << std::endl;
            std::cout << "V3: " << v3.pos << std::endl;

            glColor4f(v3.color.r, v3.color.g, v3.color.b, v3.color.a);
            glVertex3f(v3.pos.x, v3.pos.y, v3.pos.z);

            glColor4f(v2.color.r, v2.color.g, v2.color.b, v2.color.a);
            glVertex3f(v2.pos.x, v2.pos.y, v2.pos.z);

            glColor4f(v1.color.r, v1.color.g, v1.color.b, v1.color.a);
            glVertex3f(v1.pos.x, v1.pos.y, v1.pos.z);
        }/**/

        /**
        glBegin(GL_LINES);

        for (int i=0; i<m_triIndices.size(); i += 3)
        {
            int i1 = m_triIndices.at(i);
            int i2 = m_triIndices.at(i+1);
            int i3 = m_triIndices.at(i+2);

            VertexDef v1 = m_vertices.at(i1);
            VertexDef v2 = m_vertices.at(i2);
            VertexDef v3 = m_vertices.at(i3);

            std::cout << "V1: " << v1.pos << std::endl;
            std::cout << "V2: " << v2.pos << std::endl;
            std::cout << "V3: " << v3.pos << std::endl;

            glColor4f(v1.color.r, v1.color.g, v1.color.b, v1.color.a);
            glVertex3f(v1.pos.x, v1.pos.y, v1.pos.z);

            glColor4f(v2.color.r, v2.color.g, v2.color.b, v2.color.a);
            glVertex3f(v2.pos.x, v2.pos.y, v2.pos.z);

            glColor4f(v2.color.r, v2.color.g, v2.color.b, v2.color.a);
            glVertex3f(v2.pos.x, v2.pos.y, v2.pos.z);

            glColor4f(v3.color.r, v3.color.g, v3.color.b, v3.color.a);
            glVertex3f(v3.pos.x, v3.pos.y, v3.pos.z);

            glColor4f(v3.color.r, v3.color.g, v3.color.b, v3.color.a);
            glVertex3f(v3.pos.x, v3.pos.y, v3.pos.z);

            glColor4f(v1.color.r, v1.color.g, v1.color.b, v1.color.a);
            glVertex3f(v1.pos.x, v1.pos.y, v1.pos.z);
        }
        /**/

        glEnd();

        // Draw lines.
        glBegin(GL_LINES);

        for (int i=0; i<m_lineIndices.size(); i++)
        {
            int index = m_lineIndices.at(i);
            VertexDef v = m_vertices.at(index);

            glColor4f(v.color.r, v.color.g, v.color.b, v.color.a);
            glVertex3f(v.pos.x, v.pos.y, v.pos.z);
        }

        glEnd();

        glPopAttrib();
    }
}

void GraphicsManager::finalizeRender()
{
    h3dFinalizeFrame();

    m_vertices.clear();
    m_lineIndices.clear();
    m_triIndices.clear();
}

void GraphicsManager::addVertex(const Vector3& vertex, const Color& color)
{
    m_vertices.push_back(VertexDef(vertex, color));
}

void GraphicsManager::addLineIndices(int index1, int index2)
{
    m_lineIndices.push_back(index1);
    m_lineIndices.push_back(index2);
}

void GraphicsManager::addTriIndices(int index1, int index2, int index3)
{
    m_lineIndices.push_back(index1);
    m_lineIndices.push_back(index2);
    m_lineIndices.push_back(index3);
}
