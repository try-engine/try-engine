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

#ifndef TRY_SINGLETON_H
#define TRY_SINGLETON_H

#include <core/base.h>

namespace Try
{
    template<class T>
    class Singleton
    {
    protected:
        static Mutex s_mutex;
        static T* s_instance;

    private:
        // Used to access T's protected ctor.
        class SingletonAux : public T {};

    public:
        virtual ~Singleton();

        static bool hasInstance();
        static bool isInstance(T* candidate);
        static T* instance();

    protected:
        Singleton();
    };
}

using namespace Try;

template<class T>
Mutex Singleton<T>::s_mutex;

template<class T>
T* Singleton<T>::s_instance = 0;

template<class T>
Singleton<T>::Singleton()
{
    Mutex::scoped_lock lock(s_mutex);

    s_instance = static_cast<T*>(this);
}

template<class T>
Singleton<T>::~Singleton()
{
    Mutex::scoped_lock lock(s_mutex);

    if (this == s_instance)
        s_instance = 0;
}

template<class T>
bool Singleton<T>::hasInstance()
{
    Mutex::scoped_lock lock(s_mutex);

    return (s_instance != 0);
}

template<class T>
bool Singleton<T>::isInstance(T* candidate)
{
    Mutex::scoped_lock lock(s_mutex);

    return (candidate && s_instance == candidate);
}

template<class T>
T* Singleton<T>::instance()
{
    Mutex::scoped_lock lock(s_mutex);

    if (s_instance == 0)
    {
        // In ctor, the mutex is also locked.
        // This prevent a deadlock.
        lock.unlock();

        new SingletonAux();
    }

    return s_instance;
}

#endif // TRY_SINGLETON_H
