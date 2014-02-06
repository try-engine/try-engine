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

#include "object.h"
#include "behavior.h"
#include "rapidxml.h"

#define COPY_SUFFIX "_copy"

using namespace Try;

MessageName Object::Msg::renamed = "renamed";
MessageName Object::Msg::addingProperty = "addingProperty";
MessageName Object::Msg::propertyAdded = "propertyAdded";
MessageName Object::Msg::removingProperty = "removingProperty";
MessageName Object::Msg::propertyRemoved = "propertyRemoved";
MessageName Object::Msg::deletingProperty = "deletingProperty";
MessageName Object::Msg::propertyDeleted = "propertyDeleted";
MessageName Object::Msg::addingBehavior = "addingBehavior";
MessageName Object::Msg::behaviorAdded = "behaviorAdded";
MessageName Object::Msg::removingBehavior = "removingBehavior";
MessageName Object::Msg::behaviorRemoved = "behaviorRemoved";

inline void rapidxml::parse_error_handler( const char *what, void *where )
{
}

Object::Object(const String& name)
    :   m_name(name)
{
}

Object::~Object()
{
    this->unregisterAllCallbacks();
    this->removeAllProperties();
}

String Object::addProperty(Property* property)
{
    if (property && property->owner() == this)
    {
        String name = property->name();

        if (m_properties.find(name) == m_properties.end())
        {
            this->notifyMessage(Message(Object::Msg::addingProperty, property), this, 0);

            m_properties[name] = property;

            this->notifyMessage(Message(Object::Msg::propertyAdded), property);
        }

        return name;
    }
    
    return "";
}

void Object::removeProperty(const String& name)
{
    if (m_properties.find(name) != m_properties.end())
    {
        Property* prop = m_properties[name];

        this->notifyMessage(Message(Object::Msg::removingProperty), prop);

        m_properties.erase(name);
        prop->detach();

        this->notifyMessage(Message(Object::Msg::propertyRemoved, prop), this, 0);
    }
}

void Object::removeProperty(Property* property)
{
    if (property && property->owner() == this)
        this->removeProperty(property->name());
}

void Object::removeAllProperties()
{
    PropertyMap::const_iterator it(m_properties.begin());

    for (; it != m_properties.end(); ++it)
        this->removeProperty(it->first);
}

void Object::deleteProperty(const String& name)
{
    if (m_properties.find(name) != m_properties.end())
    {
        Property* prop = m_properties[name];

        this->notifyMessage(Message(Object::Msg::deletingProperty), prop);

        prop->detach();

        this->notifyMessage(Message(Object::Msg::propertyDeleted, prop), this, 0);

        delete prop;
    }
}

void Object::deleteProperty(Property* property)
{
    if (property && property->owner() == this)
        this->deleteProperty(property->name());
}

void Object::deleteAllProperties()
{
    PropertyMap::const_iterator it(m_properties.begin());

    for (; it != m_properties.end(); ++it)
        this->deleteProperty(it->first);
}

void Object::notifyMessage(const Message& msg, Property* sender)
{
    Object::notifyMessage(msg, this, sender);
}

void Object::registerCallback(Behavior* behavior, MessageCallback callback)
{
    if (m_callbacks.find(behavior) == m_callbacks.end())
    {
        this->notifyMessage(Message(Object::Msg::addingBehavior, behavior), this, 0);

        m_callbacks[behavior] = callback;

        this->notifyMessage(Message(Object::Msg::behaviorAdded, behavior), this, 0);
    }
}

void Object::unregisterCallback(Behavior* behavior)
{
    if (m_callbacks.find(behavior) != m_callbacks.end())
    {
        this->notifyMessage(Message(Object::Msg::removingBehavior, behavior), this, 0);

        m_callbacks.erase(behavior);
        behavior->removeObject(this);

        this->notifyMessage(Message(Object::Msg::behaviorRemoved, behavior), this, 0);
    }
}

void Object::unregisterAllCallbacks()
{
    if (m_callbacks.size() > 0)
    {
        MessageCallbackMap::const_iterator it(m_callbacks.begin());

        for (; it != m_callbacks.end(); ++it)
            this->unregisterCallback(it->first);
    }
}

void Object::setName(const String& name)
{
    if (name != m_name)
    {
        String old_name = m_name;

        m_name = name;

        this->notifyMessage(Message(Object::Msg::renamed, old_name), this, 0);
    }
}

String Object::name() const
{
    return m_name;
}

bool Object::is(const String& name) const
{
    return (m_name == name);
}

PropertyList Object::properties() const
{
    PropertyList properties;
    PropertyMap::const_iterator it(m_properties.begin());

    for (; it != m_properties.end(); ++it)
        properties.push_back(it->second);

    return properties;
}

StringList Object::propertyNames() const
{
    StringList names;
    PropertyMap::const_iterator it(m_properties.begin());

    for (; it != m_properties.end(); ++it)
        names.push_back(it->first);

    return names;
}

int Object::propertyCount() const
{
    return m_properties.size();
}

Property* Object::property(const String& name) const
{
    if (m_properties.find(name) != m_properties.end())
        return m_properties.at(name);

    return 0;
}

Object* Object::copy() const
{
    Object* copy_obj = new Object(this->name() + COPY_SUFFIX);

    PropertyMap::const_iterator it(m_properties.begin());

    for (; it != m_properties.end(); ++it)
    {
        Property* copy_prop = it->second->copy(copy_obj);
        copy_obj->addProperty(copy_prop);
    }

    return copy_obj;
}

String Object::serialize() const
{
    String output;

    output += String("<object name=\"") + this->name() + "\">\n";

    PropertyMap::const_iterator it(m_properties.begin());

    for (; it != m_properties.end(); ++it)
        output += it->second->serialize();

    output += "</object>\n";

    return output;
}

ObjectList Object::deserialize(XmlNode* node)
{
    ObjectList results;

    if (node && String(node->name()) == "object")
    {
        while (node)
        {
            String name = node->first_attribute("name")->value();

            if (!name.empty())
            {
                Object* obj = new Object(name);

                Property::deserialize(node->first_node("property"), obj);

                results.push_back(obj);
            }

            node = node->next_sibling("object");
        }
    }

    return results;
}

void Object::notifyMessage(const Message& msg, Object* sender, Property* property)
{
    if (sender && (!property || property->owner() == sender))
    {
        MessageCallbackMap::iterator begin = sender->m_callbacks.begin();
        MessageCallbackMap::iterator end = sender->m_callbacks.end();
        MessageCallbackMap::iterator it;

        for (it=begin; it!=end; ++it)
        {
            Behavior* owner = it->first;
            MessageCallback callback = it->second;
            (owner->*callback)(msg, sender, property);
        }
    }
}
