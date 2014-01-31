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

#include "behavior.h"

using namespace Try;

Behavior::Behavior(const ObjectList& objects)
{
    this->watchObjects(objects);
}

Behavior::~Behavior()
{
    this->removeAllObjects();
}

ObjectList Behavior::objects() const
{
    return m_objects;
}

int Behavior::objectCount() const
{
    return m_objects.size();
}

StringList Behavior::objectNames() const
{
    StringList names;

    for (int i=0; i < this->objectCount(); i++)
    {
        Object* object = this->object(i);
        names.push_back(object->name());
    }

    return names;
}

Object* Behavior::object(int id) const
{
    if (id > -1 && id < this->objectCount())
        return m_objects[id];

    return 0;
}

Object* Behavior::object(const String& name) const
{
    return this->object(this->objectIdFromName(name));
}

bool Behavior::isWatching(Object* object) const
{
    int id = this->objectIdFromName(object->name());

    return (id != -1);
}

int Behavior::objectIdFromName(const String& name) const
{
    for (int i=0; i<this->objectCount(); i++)
    {
        Object* object = this->object(i);
        if (object && object->name() == name)
            return i;
    }

    return -1;
}

int Behavior::watchObject(Object* object)
{
    if (object)
    {
        int id = this->objectIdFromName(object->name());

        if (id == -1)
        {
            id = m_objects.size();
            m_objects.push_back(object);
            object->registerCallback(this, &Behavior::onMessage);
        }

        return id;
    }
    
    return -1;
}

void Behavior::watchObjects(const ObjectList& objects)
{
    for (int i=0; i < objects.size(); i++)
        this->watchObject(objects[i]);
}

void Behavior::removeObject(int id)
{
    if (id > -1 && id < this->objectCount())
    {
        Object* object = m_objects[id];
        m_objects.erase(m_objects.begin()+id);
        object->unregisterCallback(this);
    }
}

void Behavior::removeObject(const String& name)
{
    this->removeObject(this->objectIdFromName(name));
}

void Behavior::removeObject(Object* object)
{
    if (object)
        this->removeObject(object->name());
}

void Behavior::removeAllObjects()
{
    for (int i=this->objectCount(); i>0; i--)
        this->removeObject(i-1);
}

void Behavior::deleteObject(int id)
{
    if (id > -1 && id < this->objectCount())
    {
        Object* object = m_objects[id];
        m_objects.erase(m_objects.begin()+id);
        object->unregisterCallback(this);
        delete object;
    }
}

void Behavior::deleteObject(const String& name)
{
    this->deleteObject(this->objectIdFromName(name));
}

void Behavior::deleteObject(Object* object)
{
    if (object)
        this->deleteObject(object->name());
}

void Behavior::deleteAllObjects()
{
    for (int i=this->objectCount(); i>0; i--)
        this->deleteObject(i-1);
}
