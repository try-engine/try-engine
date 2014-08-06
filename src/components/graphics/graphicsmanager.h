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

#ifndef TRY_GRAPHICSMANAGER_H
#define TRY_GRAPHICSMANAGER_H

#include <graphics/rendercontext.h>
#include <core/listenable.h>
#include <core/singleton.h>

#define graphics GraphicsManager::instance()

#define TRY_DEFAULT_SEGMENT_COUNT 48

namespace Try
{
    class GraphicsManager : public Singleton<GraphicsManager>,
                            public Listenable<RenderListener>,
                            public Listenable<SceneTransformableListener>,
                            public Listenable<CameraListener>,
                            public Listenable<LightListener>
    {
    public:
        enum TransformableFlags
        {
            NoDraw          = 1,
            NoCastShadow    = 2,
            NoRayQuery      = 4,
            Inactive        = NoDraw | NoCastShadow | NoRayQuery
        };

    protected:
        RenderContextList m_renderContexts;

    private:
        struct AnimData
        {
            ResourceHandle handle;
            TransformableHandle owner;
            float time;
            float weight;
            int layer;
            bool running;
        };

        std::vector<AnimData> m_animations;
        VertexList m_vertices;
        IndexList m_lineIndices;
        IndexList m_triIndices;

    public:
        GraphicsManager(RenderContext* rc = 0);
        virtual ~GraphicsManager();

        // Render contexts.
        void registerRenderContext(RenderContext* rc);
        void unregisterRenderContext(RenderContext* rc);

        void renderOneFrame(double dt = 0);

        int renderContextCount() const;
        RenderContext* renderContext(int index) const;
        bool hasRenderContext(RenderContext* rc) const;

        // Resources.
        void removeResource(const ResourceHandle& res);

        ResourceHandle createTexture(
            const String& name,
            const unsigned char* data,
            const Vector2& size
        );

        ResourceHandle loadTexture(const String& filename);

        Vector2 textureSize(const ResourceHandle& res) const;

        ResourceHandle createGeometry(
            const String& name,
            const VertexList& vertices,
            const IndexList& indices
        );

        ResourceHandle loadAnimation(
            const TransformableHandle& handle,
            const String& filename,
            float weight = 1,
            int layer = 0
        );

        ResourceHandle loadAnimation(
            const TransformableHandle& handle,
            const ResourceHandle& anim_res,
            float weight = 1,
            int layer = 0
        );

        void changeAnimationWeight(const TransformableHandle& handle, int animation_id, float weight);
        void updateAnimation(const TransformableHandle& handle, int animation_id, float dt);
        void resetAnimation(const TransformableHandle& handle, int animation_id);

        int animationCount(const TransformableHandle& handle) const;
        float animationTime(const TransformableHandle& handle, int animation_id) const;
        float animationWeight(const TransformableHandle& handle, int animation_id) const;

        // Transformables.
        void setParent(const TransformableHandle& handle, const TransformableHandle& parent);
        void setFlag(const TransformableHandle& handle, TransformableFlags flag, bool value = true);
        void setFlags(const TransformableHandle& handle, int flags);
        void setTransform(const TransformableHandle& handle, const Transform& t);
        void setTransform(
            const TransformableHandle& handle,
            const Vector3& pos,
            const Vector3& rot,
            const Vector3& scale
        );

        void remove(const TransformableHandle& handle);

        String name(const TransformableHandle& handle) const;
        int flags(const TransformableHandle& handle) const;
        Transform transform(const TransformableHandle& handle) const;
        TransformableHandle parent(const TransformableHandle& handle) const;
        AxisAlignedBoundingBox worldAABB(const TransformableHandle& handle) const;

        // Models.
        TransformableHandle loadModel(
            const String& name,
            const ResourceHandle& model_res,
            const Transform& t = Transform(),
            const TransformableHandle& parent = TransformableRoot
        );

        TransformableHandle loadModel(
            const String& filename,
            const Transform& t = Transform(),
            const TransformableHandle& parent = TransformableRoot
        );

        // Particles.
        TransformableHandle loadParticles(
            const String& name,
            const ResourceHandle& material,
            const ResourceHandle& effect,
            int max_particles,
            int respawn_count,
            const Transform& t = Transform(),
            const TransformableHandle& parent = TransformableRoot
        );

        TransformableHandle loadParticles(
            const String& filename,
            const Transform& t = Transform(),
            const TransformableHandle& parent = TransformableRoot
        );

        void updateParticles(const TransformableHandle& handle, float dt);

        // Cameras.
        TransformableHandle loadCamera(
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

        TransformableHandle loadCamera(
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

        void setupCameraViewport(const TransformableHandle& cam, int width, int height, float fov, float near_clip, float far_clip);

        int cameraViewportWidth(const TransformableHandle& cam) const;
        int cameraViewportHeight(const TransformableHandle& cam) const;
        float cameraViewportFOV(const TransformableHandle& cam) const;
        float cameraViewportNearClip(const TransformableHandle& cam) const;
        float cameraViewportFarClip(const TransformableHandle& cam) const;

        Vector3 projectFromCameraToWorld(const TransformableHandle& cam, float nx, float ny) const;
        Vector3 projectFromCameraToWorld(const TransformableHandle& cam, float nx, float ny, float clip) const;
        TransformableHandle pickFromCamera(const TransformableHandle& cam, float nx, float ny) const;

        // Lights.
        TransformableHandle loadLight(
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

        void setLightRadius(const TransformableHandle& light, float radius);
        void setLightFOV(const TransformableHandle& light, float fov);
        void setLightColor(const TransformableHandle& light, const Color& c);
        void setLightLightingContext(const TransformableHandle& light, const String& ctx);
        void setLightShadowContext(const TransformableHandle& light, const String& ctx);

        float lightRadius(const TransformableHandle& light) const;
        float lightFOV(const TransformableHandle& light) const;
        Color lightColor(const TransformableHandle& light) const;
        String lightLightingContext(const TransformableHandle& light) const;
        String lightShadowContext(const TransformableHandle& light) const;

        // Primitives.
        void drawLine(const Vector3& start, const Vector3& end, const Color& color = Colors::White);
        void drawCircle(const Vector3& center, float radius, int segment_count = TRY_DEFAULT_SEGMENT_COUNT, const Color& color = Colors::White);
        void drawQuad(const Vector3& center, const float width, float height, const Color& color = Colors::White);
        void drawGrid(const Vector3& center, const Color& color = Colors::White, float cell_size = 20, int numcols = 30, int numrows = 30);
        void drawBox(const Vector3& center, const Vector3& size, const Color& color = Colors::White);
        void drawCone(const Vector3& center, float radius, float length, int segment_count = TRY_DEFAULT_SEGMENT_COUNT, const Color& color = Colors::White);
        void drawCylinder(const Vector3& center, float radius, float length, int segment_count = TRY_DEFAULT_SEGMENT_COUNT, const Color& color = Colors::White);
        void drawGeometry(const Vector3& center, const VertexList& vertices, const IndexList& indices, const ResourceHandle& texture = 0);

    protected:
        void renderOnContexts(float dt);
        void renderRawGeometries(const TransformableHandle& cam);
        void finalizeRender();
        void addVertex(const Vector3& vertex, const Color& color);
        void addLineIndices(int index1, int index2);
        void addTriIndices(int index1, int index2, int index3);
    };
}

#endif // TRY_GRAPHICSMANAGER_H
