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

#include <graphics/scenetransformable.h>
#include <graphics/graphicsmanager.h>

using namespace Try;

MessageName SceneTransformable::Msg::handleChanged = "handleChanged";
MessageName SceneTransformable::Msg::parentChanged = "parentChanged";
MessageName SceneTransformable::Msg::transformChanged = "transformChanged";
MessageName SceneTransformable::Msg::flagsChanged = "flagsChanged";

std::list<SceneTransformable*> SceneTransformable::s_cache;

SceneTransformable::~SceneTransformable()
{
    graphics->remove(m_handle);

    s_cache.remove(this);
}

void SceneTransformable::setHandle(const TransformableHandle& handle)
{
    TransformableHandle old = m_handle;

    if (old != handle)
    {
        m_handle = handle;

        this->notifyMessage(Message(SceneTransformable::Msg::handleChanged, old, m_handle));
    }
}

void SceneTransformable::setParentHandle(const TransformableHandle& parent)
{
    TransformableHandle old = graphics->parent(m_handle);

    if (old != parent)
    {
        graphics->setParent(m_handle, parent);

        this->notifyMessage(Message(SceneTransformable::Msg::parentChanged, m_handle, old, parent));
    }
}

void SceneTransformable::setTransform(const Transform& t)
{
    Transform old = this->transform();

    if (old != t)
    {
        graphics->setTransform(m_handle, t);

        this->notifyMessage(Message(SceneTransformable::Msg::transformChanged, m_handle, old, t));
    }
}

TransformableHandle SceneTransformable::handle() const
{
    return m_handle;
}

TransformableHandle SceneTransformable::parentHandle() const
{
    return graphics->parent(m_handle);
}

String SceneTransformable::handleName() const
{
    return graphics->name(m_handle);
}

Transform SceneTransformable::transform() const
{
    return graphics->transform(m_handle);
}

AxisAlignedBoundingBox SceneTransformable::worldAABB() const
{
    return graphics->worldAABB(m_handle);
}

std::vector<SceneTransformable*> SceneTransformable::query(const TransformableHandle& handle)
{
    std::vector<SceneTransformable*> results;
    std::list<SceneTransformable*>::iterator it;

    for (it = s_cache.begin(); it != s_cache.end(); it++)
    {
        SceneTransformable* t = *it;
        if (t->m_handle == handle)
            results.push_back(t);
    }

    return results;
}

SceneTransformable::SceneTransformable(const String &name, Object* owner, const TransformableHandle& handle)
    : Property(name, owner),
      m_handle(handle)
{
    s_cache.push_back(this);
}

void SceneTransformable::onParentChanged(const TransformableHandle& old, const TransformableHandle& parent)
{
    this->notifyMessage(Message(SceneTransformable::Msg::parentChanged, old, parent));
}

void SceneTransformable::onTransformChanged(const Transform& old, const Transform& t)
{
    this->notifyMessage(Message(SceneTransformable::Msg::transformChanged, old, t));
}

void SceneTransformable::onFlagsChanged(int old, int flags)
{
    this->notifyMessage(Message(SceneTransformable::Msg::flagsChanged, old, flags));
}

void SceneTransformable::onRemoved()
{
    this->setHandle(0);
}
