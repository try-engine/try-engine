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

#include <graphics/model3d.h>
#include <graphics/graphicsmanager.h>

using namespace Try;

PropertyName Model3D::name  = "try.graphics.model3d";

Model3D::Model3D(
    Object* owner,
    const TransformableHandle& model
)
    : SceneTransformable(Model3D::name, owner, model)
{    
    ((Listenable<RenderListener>*)graphics)->addListener(this);

    Property::registerDeserialize(Model3D::name, &Model3D::deserializeThis);
}

Model3D::Model3D(
    Object* owner,
    const String& filename,
    const Transform& t,
    const TransformableHandle& parent
)
    : SceneTransformable(Model3D::name, owner, graphics->loadModel(filename, t, parent))
{
    ((Listenable<RenderListener>*)graphics)->addListener(this);

    Property::registerDeserialize(Model3D::name, &Model3D::deserializeThis);
}

Model3D::~Model3D()
{
    ((Listenable<RenderListener>*)graphics)->removeListener(this);

    this->removeAllAnimations();
}

int Model3D::addAnimation(const String& filename, float weight, int layer)
{
    graphics->loadAnimation(m_handle, filename, weight, layer);

    return graphics->animationCount(m_handle) - 1;
}

void Model3D::removeAllAnimations()
{
    for (int i=this->animationCount(); i>0; i--)
        this->removeAnimation(i-1);
}

void Model3D::removeAnimation(int animation_id)
{
    this->stopAnimation(animation_id);

    // TODO:
    //graphics->removeAnimation(m_handle, animation_id);
}

void Model3D::resetAllAnimations()
{
    for (int i=this->animationCount(); i>0; i--)
        this->resetAnimation(i-1);
}

void Model3D::resetAnimation(int animation_id)
{
    graphics->resetAnimation(m_handle, animation_id);
}

void Model3D::runAllAnimations(float speed)
{
    for (int i=0; i<this->animationCount(); i++)
        this->runAnimation(i, speed);
}

void Model3D::runAnimation(int animation_id, float speed)
{
    m_runningAnimations[animation_id] = speed;
}

void Model3D::pauseAllAnimations()
{
    for (int i=this->animationCount(); i>0; i--)
        this->pauseAnimation(i-1);
}

void Model3D::pauseAnimation(int animation_id)
{
    this->changeAnimationWeight(animation_id, 0);
    m_runningAnimations[animation_id] = 0;
}

void Model3D::stopAllAnimations()
{
    for (int i=this->animationCount(); i>0; i--)
        this->stopAnimation(i-1);
}

void Model3D::stopAnimation(int animation_id)
{
    this->pauseAnimation(animation_id);
    this->resetAnimation(animation_id);
    m_runningAnimations.erase(animation_id);
}

void Model3D::changeAnimationWeight(int animation_id, float weight)
{
    graphics->changeAnimationWeight(m_handle, animation_id, weight);
}

int Model3D::animationCount() const
{
    graphics->animationCount(m_handle);
}

bool Model3D::isAnimationRunning(int animation_id) const
{
    if (m_runningAnimations.find(animation_id) == m_runningAnimations.end())
        return false;

    return true;
}

float Model3D::animationTime(int animation_id) const
{
    return graphics->animationTime(m_handle, animation_id);
}

float Model3D::animationWeight(int animation_id) const
{
    return graphics->animationWeight(m_handle, animation_id);
}

Property* Model3D::copy(Object* owner) const
{
    return 0;
}

String Model3D::serialize() const
{
    return "";
}

Property* Model3D::deserializeThis(XmlNode* node, Object* owner)
{
    Property* result = 0;

    if (node && String(node->name()) == "property")
    {
        String name = node->first_attribute("name")->value();

        if (name == Model3D::name)
        {
            String filename = node->first_attribute("filename")->value();

            Transform transform; // = node->first_attribute("transform")->value();;
            TransformableHandle parent = 0;

            result = new Model3D(owner, filename, transform, parent);
        }
    }

    return result;
}

void Model3D::onRenderStarted(double dt)
{
    std::map<int, float>::iterator it = m_runningAnimations.begin();

    while (it != m_runningAnimations.end())
    {
        graphics->updateAnimation(m_handle, (*it).first, dt * (*it).second);
        it++;
    }
}
