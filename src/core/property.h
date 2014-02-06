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

#ifndef TRY_PROPERTY_H
#define TRY_PROPERTY_H

#include "message.h"
#include <map>

namespace Try
{
    class Object;
    class Property;

    typedef std::vector<Property*> PropertyList;
    typedef std::map<String,Property*> PropertyMap;
    typedef const String PropertyName;

    class Property
    {
    public:
        typedef Property* (*PropertyDeserialize) (XmlNode* node, Object* owner);

    protected:
        String m_name;

        typedef std::map<String, PropertyDeserialize> PropertyDeserializeMap;

    private:
        Object* m_owner;

        static PropertyDeserializeMap s_propertyRegistry;

    public:
        virtual ~Property();

        void detach();

        String name() const;
        bool is(const String& name) const;
        Object* owner() const;

        virtual Property* copy(Object* owner) const;
        virtual String serialize() const;

        static PropertyList deserialize(XmlNode* node, Object* owner);
        static void registerDeserialize(const String& name, const PropertyDeserialize& deserialize);

    protected:
        Property(const String& name, Object* owner);

        void notifyMessage(const Message& msg);
        void setName(const String& name);
    };
}

#endif // TRY_PROPERTY_H
