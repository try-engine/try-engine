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

#ifndef TRY_LISTENABLE_H
#define TRY_LISTENABLE_H

#include <vector>

namespace Try
{
    template<class T>
    class Listenable
    {
    public:
        typedef std::vector<T*> list_type;

    protected:
        list_type m_listeners;

    public:
        Listenable();
        virtual ~Listenable();

        void addListener(T* listener);
        void removeListener(T* listener);

        bool hasListeners() const;
        bool hasListener(T* listener) const;
        list_type listeners() const;
        unsigned int listenerCount() const;

        static Listenable<T>* bind(Listenable<T>* obj);
    };

    template<class C>
    Listenable<C>* bind(Listenable<C>* obj)
    {
        return Listenable<C>::bind(obj);
    }
}

using namespace Try;

template<class T>
Listenable<T>::Listenable()
{
}

template<class T>
Listenable<T>::~Listenable()
{
}

template<class T>
void Listenable<T>::addListener(T* listener)
{
    if (listener && !this->hasListener(listener))
        m_listeners.push_back(listener);
}

template<class T>
void Listenable<T>::removeListener(T* listener)
{
    if (listener)
    {
        int size = m_listeners.size();

        for (int i=0; i<size; i++)
        {
            if (m_listeners.at(i) == listener)
            {
                m_listeners.erase(m_listeners.begin()+i);
                break;
            }
        }
    }
}

template<class T>
bool Listenable<T>::hasListeners() const
{
    return !m_listeners.empty();
}

template<class T>
bool Listenable<T>::hasListener(T* listener) const
{
    if (listener)
    {
        int size = m_listeners.size();

        for (int i=0; i<size; i++)
            if (m_listeners.at(i) == listener)
                return true;
    }

    return false;
}

template<class T>
typename Listenable<T>::list_type Listenable<T>::listeners() const
{
    return m_listeners;
}

template<class T>
unsigned int Listenable<T>::listenerCount() const
{
    return m_listeners.size();
}

template<class T>
Listenable<T>* Listenable<T>::bind(Listenable<T>* obj)
{
    return static_cast<Listenable<T>*>(obj);
}

#endif // TRY_LISTENABLE_H
