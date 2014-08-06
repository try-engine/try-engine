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

#include <core/try.h>

class SimpleSingleton : public Singleton<SimpleSingleton> {};

class ProtectedSingleton : public Singleton<ProtectedSingleton>
{
protected:
    ProtectedSingleton() {}
};

class TestListenerA
{
public:
    Try::String state;

    void onA()
    {
        if (state.empty())
            state = "called";
        else
            state = "re-called";
    }
};

class TestListenerB
{
};

class TestListenable : public Try::Listenable<TestListenerA>
{
public:
    void notify()
    {
        Try::Listenable<TestListenerA>::list_type listeners = this->listeners();
        for (int i= 0; i<listeners.size(); ++i)
            listeners[i]->onA();
    }
};

class TestMultiListenable :
        public Try::Listenable<TestListenerA>,
        public Try::Listenable<TestListenerB>
{
};
