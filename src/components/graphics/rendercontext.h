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

#ifndef TRY_RENDERCONTEXT_H
#define TRY_RENDERCONTEXT_H

#include <graphics/base.h>
#include <core/listenable.h>

namespace Try
{
    class RenderContext : public Listenable<RenderContextListener>
    {
    protected:
        String m_name;
        TransformableHandle m_activeCamera;

    public:
        RenderContext(const String& name, const TransformableHandle& camera = 0);
        virtual ~RenderContext();

        void activateContext();
        void updateContext();
        void setActiveCamera(const TransformableHandle& camera);

        virtual int width() const = 0;
        virtual int height() const = 0;

        String name() const;
        TransformableHandle activeCamera() const;
        Vector3 projectToWorld(float nx, float ny) const;
        Vector3 projectToWorld(float nx, float ny, float clip) const;

    protected:
        virtual void onActivateContext() = 0;
        virtual void onUpdateContext() = 0;
        virtual void onCameraChanged(const TransformableHandle& camera) {}

        void resizeCameraViewport(int width, int height);
    };

    typedef std::vector<RenderContext*> RenderContextList;
}

#endif // TRY_RENDERCONTEXT_H
