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

#include <graphics/particlesemitter.h>
#include <graphics/graphicsmanager.h>

using namespace Try;

PropertyName ParticlesEmitter::name  = "try.graphics.particlesemitter";

ParticlesEmitter::ParticlesEmitter(Object* owner, const TransformableHandle& particles)
    : SceneTransformable(ParticlesEmitter::name, owner, particles)
{
    ((Listenable<RenderListener>*)graphics)->addListener(this);

    Property::registerDeserialize(ParticlesEmitter::name, &ParticlesEmitter::deserializeThis);
}

ParticlesEmitter::ParticlesEmitter(
    Object* owner,
    const String& filename,
    const Transform& t,
    const TransformableHandle& parent
)
    : SceneTransformable(ParticlesEmitter::name, owner, graphics->loadParticles(filename, t, parent))
{
    ((Listenable<RenderListener>*)graphics)->addListener(this);

    Property::registerDeserialize(ParticlesEmitter::name, &ParticlesEmitter::deserializeThis);
}

ParticlesEmitter::~ParticlesEmitter()
{
    ((Listenable<RenderListener>*)graphics)->removeListener(this);
}

Property* ParticlesEmitter::copy(Object* owner) const
{
    return 0;
}

String ParticlesEmitter::serialize() const
{
    return "";
}

Property* ParticlesEmitter::deserializeThis(XmlNode* node, Object* owner)
{
    Property* result = 0;

    if (node && String(node->name()) == "property")
    {
        String name = node->first_attribute("name")->value();

        if (name == ParticlesEmitter::name)
        {
            String filename = node->first_attribute("filename")->value();

            Transform transform; // = node->first_attribute("transform")->value();;
            TransformableHandle parent = 0;

            result = new ParticlesEmitter(owner, filename, transform, parent);
        }
    }

    return result;
}

void ParticlesEmitter::onRenderStarted(double dt)
{
    graphics->updateParticles(m_handle, dt);
}
