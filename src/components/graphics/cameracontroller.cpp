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

#include <graphics/cameracontroller.h>
#include <graphics/graphicsmanager.h>

using namespace Try;

PropertyName CameraController::name  = "try.graphics.cameracontroller";

MessageName CameraController::Msg::viewportChanged = "viewportChanged";

CameraController::CameraController(
    Object* owner,
    const TransformableHandle& camera
)
    : SceneTransformable(CameraController::name, owner, camera)
{
    ((Listenable<CameraListener>*)graphics)->addListener(this);
}

CameraController::CameraController(
    Object* owner,
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
    : SceneTransformable(CameraController::name, owner, graphics->loadCamera(name, pipeline, width, height, fov, near_clip, far_clip, t, parent))
{
    ((Listenable<CameraListener>*)graphics)->addListener(this);
}

CameraController::CameraController(
    Object* owner,
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
    : SceneTransformable(CameraController::name, owner, graphics->loadCamera(name, pipeline_filename, width, height, fov, near_clip, far_clip, t, parent))
{
    ((Listenable<CameraListener>*)graphics)->addListener(this);
}

CameraController::~CameraController()
{
    ((Listenable<CameraListener>*)graphics)->removeListener(this);
}

void CameraController::setViewport(int width, int height, float fov, float near_clip, float far_clip)
{
    graphics->setupCameraViewport(m_handle, width, height, fov, near_clip, far_clip);
}

int CameraController::viewportWidth() const
{
    return graphics->cameraViewportWidth(m_handle);
}

int CameraController::viewportHeight() const
{
    return graphics->cameraViewportHeight(m_handle);
}

float CameraController::viewportFOV() const
{
    return graphics->cameraViewportFOV(m_handle);
}

float CameraController::viewportNearClip() const
{
    return graphics->cameraViewportNearClip(m_handle);
}

float CameraController::viewportFarClip() const
{
    return graphics->cameraViewportFarClip(m_handle);
}

Vector3 CameraController::projectToWorld(float nx, float ny) const
{
    return graphics->projectFromCameraToWorld(m_handle, nx, ny);
}

TransformableHandle CameraController::pick(float nx, float ny) const
{
    return graphics->pickFromCamera(m_handle, nx, ny);
}

Property* CameraController::copy(Object* owner) const
{
    return new CameraController(owner, m_handle);
}

String CameraController::serialize() const
{
    return "";
}

void CameraController::onViewportChanged(int width, int height, float fov, float near_clip, float far_clip)
{
    this->notifyMessage(Message(CameraController::Msg::viewportChanged, width, height, fov, near_clip, far_clip));
}
