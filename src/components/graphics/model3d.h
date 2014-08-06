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

#ifndef TRY_MODEL3D_H
#define TRY_MODEL3D_H

#include <graphics/scenetransformable.h>

namespace Try
{
    class Model3D : public SceneTransformable,
                    protected RenderListener
    {
    public:
        static PropertyName name;

        struct Msg
        {
            // No messages.
        };

    private:
        std::map<int, float> m_runningAnimations;

    public:
        Model3D(
            Object* owner,
            const TransformableHandle& model
        );
        Model3D(
            Object* owner,
            const String& filename,
            const Transform& t = Transform(),
            const TransformableHandle& parent = TransformableRoot
        );
        virtual ~Model3D();

        int addAnimation(
            const String& filename,
            float weight = 1,
            int layer = 0
        );

        void removeAllAnimations();
        void removeAnimation(int animation_id);

        void resetAllAnimations();
        void resetAnimation(int animation_id);

        void runAllAnimations(float speed = 1);
        void runAnimation(int animation_id, float speed = 1);

        void pauseAllAnimations();
        void pauseAnimation(int animation_id);

        void stopAllAnimations();
        void stopAnimation(int animation_id);

        void changeAnimationWeight(int animation_id, float weight);

        int animationCount() const;
        bool isAnimationRunning(int animation_id) const;
        float animationWeight(int animation_id) const;
        float animationTime(int animation_id) const;

        Property* copy(Object* owner) const;
        String serialize() const;

        static Property* deserializeThis(XmlNode* node, Object* owner);

    protected:
        void onRenderStarted(double dt);
    };
}

#endif // TRY_MODEL3D_H
