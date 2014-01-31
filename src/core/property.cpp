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

#include "property.h"
#include "object.h"

using namespace Try;

Property::PropertyDeserializeMap Property::s_propertyRegistry;

Property::Property(const String& name, Object* owner)
    :   m_name(name),
        m_owner(owner)
{
    if (m_owner)
        m_owner->addProperty(this);
}

Property::~Property()
{
    this->detach();
}

void Property::detach()
{
    if (m_owner)
    {
        Object* owner = m_owner;
        m_owner = 0;

        owner->removeProperty(this);
    }
}

String Property::name() const
{
    return m_name;
}

bool Property::is(const String& name) const
{
    return (m_name == name);
}

Object* Property::owner() const
{
    return m_owner;
}

Property* Property::copy(Object* owner) const
{
    return 0;
}

String Property::serialize() const
{
    return String("<property name=\"") + this->name() + "\" />\n";
}

PropertyList Property::deserialize(XmlNode* node, Object* owner)
{
    PropertyList results;

    if (node && String(node->name()) == "property")
    {
        while (node)
        {
            String name = node->first_attribute("name")->value();

            if (!name.empty() && s_propertyRegistry.find(name) != s_propertyRegistry.end())
            {
                PropertyDeserialize func_ptr = s_propertyRegistry.at(name);
                Property* property = (*func_ptr)(node, owner);
                results.push_back(property);
            }

            node = node->next_sibling("object");
        }
    }

    return results;
}

void Property::registerDeserialize(const String& name, const PropertyDeserialize& deserialize)
{
    if (deserialize)
        s_propertyRegistry[name] = deserialize;
}

void Property::notifyMessage(const Message& msg)
{
    if (m_owner)
        m_owner->notifyMessage(msg, this);
}

void Property::setName(const String& name)
{
    m_name = name;
}
