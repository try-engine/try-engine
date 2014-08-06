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

#ifndef TRY_BEHAVIOR_H
#define TRY_BEHAVIOR_H

#include <core/object.h>

namespace Try
{
    class Behavior
    {
    protected:
        ObjectList m_objects;

    public:
        Behavior(const ObjectList& objects = ObjectList());
        virtual ~Behavior();

        ObjectList objects() const;
        StringList objectNames() const;
        int objectCount() const;

        Object* object(int id) const;
        Object* object(const String& name) const;

        bool isWatching(Object* object) const;
        int objectIdFromName(const String& name) const;

        int watchObject(Object* object);
        void watchObjects(const ObjectList& objects);
        void removeObject(int id);
        void removeObject(const String& name);
        void removeObject(Object* object);
        void removeAllObjects();
        void deleteObject(int id);
        void deleteObject(const String& name);
        void deleteObject(Object* object);
        void deleteAllObjects();

    protected:
        virtual void onMessage(const Message& msg, Object* sender, Property* property) = 0;
    };

    typedef std::vector<Behavior*> BehaviorList;
}

#endif // TRY_BEHAVIOR_H
