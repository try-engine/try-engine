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

#include <graphics/rendercontext.h>
#include <graphics/graphicsmanager.h>
#include <GLFW/glfw3.h>

using namespace Try;

RenderContext::RenderContext(const String& name, const TransformableHandle& camera)
    :   m_name(name),
        m_activeCamera(camera)
{
}

RenderContext::~RenderContext()
{
    graphics->unregisterRenderContext(this);

    this->setActiveCamera(0);
}

void RenderContext::activateContext()
{
    this->onActivateContext();

    int size = m_listeners.size();

    for (int i=0; i<size; i++)
        m_listeners.at(i)->onContextActivated(this);
}


void RenderContext::updateContext()
{
    this->onUpdateContext();

    int size = m_listeners.size();

    for (int i=0; i<size; i++)
        m_listeners.at(i)->onContextUpdated(this);
}

void RenderContext::setActiveCamera(const TransformableHandle& camera)
{
    if (camera != m_activeCamera)
        m_activeCamera = camera;

    this->onCameraChanged(camera);

    int size = m_listeners.size();

    for (int i=0; i<size; i++)
        m_listeners.at(i)->onCameraChanged(this, camera);
}

String RenderContext::name() const
{
    return m_name;
}

TransformableHandle RenderContext::activeCamera() const
{
    return m_activeCamera;
}

Vector3 RenderContext::projectToWorld(float nx, float ny) const
{
    if (m_activeCamera)
        return graphics->projectFromCameraToWorld(m_activeCamera, nx, ny);

    return Vector3::Zero;
}

Vector3 RenderContext::projectToWorld(float nx, float ny, float clip) const
{
    if (m_activeCamera)
        return graphics->projectFromCameraToWorld(m_activeCamera, nx, ny, clip);

    return Vector3::Zero;
}

void RenderContext::resizeCameraViewport(int width, int height)
{
    if (m_activeCamera)
    {
        float fov = graphics->cameraViewportFOV(m_activeCamera);
        float near = graphics->cameraViewportNearClip(m_activeCamera);
        float far = graphics->cameraViewportFarClip(m_activeCamera);

        graphics->setupCameraViewport(m_activeCamera, width, height, fov, near, far);
    }
}
