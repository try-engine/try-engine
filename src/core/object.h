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

#ifndef TRY_OBJECT_H
#define TRY_OBJECT_H

#include <core/property.h>
#include <map>

namespace Try
{
    class Behavior;
    class Object;

    typedef std::vector<Object*> ObjectList;
    typedef void (Behavior::*MessageCallback) (const Message&, Object*, Property*);
    typedef std::map<Behavior*, MessageCallback> MessageCallbackMap;

    class Object
    {
    public:
        struct Msg
        {
            static MessageName renamed;
            static MessageName addingProperty;
            static MessageName propertyAdded;
            static MessageName removingProperty;
            static MessageName propertyRemoved;
            static MessageName deletingProperty;
            static MessageName propertyDeleted;
            static MessageName addingBehavior;
            static MessageName behaviorAdded;
            static MessageName removingBehavior;
            static MessageName behaviorRemoved;
        };

    protected:
        String m_name;
        PropertyMap m_properties;
        MessageCallbackMap m_callbacks;

    public:
        Object(const String& name);
        virtual ~Object();

        String addProperty(Property* property);
        void removeProperty(const String& name);
        void removeProperty(Property* property);
        void removeAllProperties();
        void deleteProperty(const String& name);
        void deleteProperty(Property* property);
        void deleteAllProperties();

        void notifyMessage(const Message& msg, Property* sender);
        void registerCallback(Behavior* behavior, MessageCallback callback);
        void unregisterCallback(Behavior* behavior);
        void unregisterAllCallbacks();

        void setName(const String& name);

        String name() const;
        bool is(const String& name) const;

        PropertyList properties() const;
        StringList propertyNames() const;
        int propertyCount() const;

        Property* property(const String& name) const;

        template<class T>
        T* property() const;

        template<class T>
        T* property(const String& name) const { return static_cast<T*>(this->property(name)); }

        virtual Object* copy() const;
        virtual String serialize() const;

        static ObjectList deserialize(XmlNode* node);

    protected:
        static void notifyMessage(const Message &msg, Object* sender, Property* property);
    };

    template<class T>
    T* Object::property() const
    {
        PropertyMap::const_iterator it = m_properties.begin();
        while (it != m_properties.end())
        {
            T* prop = dynamic_cast<T*>(this->property(it->second->name()));
            if (prop)
                return prop;

            ++it;
        }

        return 0;
    }
}

#endif // TRY_OBJECT_H
