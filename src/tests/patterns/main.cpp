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

#include <tests/catch.hpp>
#include "data.h"

TEST_CASE( "Test a simple Singleton", "[patterns][singleton][simple]" )
{
    REQUIRE(SimpleSingleton::hasInstance() == false);

    {
        SimpleSingleton ss1;

        REQUIRE(SimpleSingleton::hasInstance() == true);
        REQUIRE(SimpleSingleton::isInstance(&ss1) == true);
        REQUIRE(SimpleSingleton::instance() == &ss1);

        SimpleSingleton ss2;

        REQUIRE(SimpleSingleton::hasInstance() == true);
        REQUIRE(SimpleSingleton::isInstance(&ss1) == false);
        REQUIRE(SimpleSingleton::isInstance(&ss2) == true);
        REQUIRE(SimpleSingleton::instance() == &ss2);
    }

    REQUIRE(SimpleSingleton::hasInstance() == false);
}

TEST_CASE( "Test a protected Singleton", "[patterns][singleton][protected]" )
{
    REQUIRE(ProtectedSingleton::hasInstance() == false);

    ProtectedSingleton* ps = ProtectedSingleton::instance();

    REQUIRE(ProtectedSingleton::hasInstance() == true);
    REQUIRE(ProtectedSingleton::isInstance(ps) == true);
    REQUIRE(ps != 0);

    delete ps;
    ps = 0;

    REQUIRE(ProtectedSingleton::hasInstance() == false);
    REQUIRE(ProtectedSingleton::isInstance(ps) == false);
    REQUIRE(ps == 0);
}

TEST_CASE( "Test a single Listenable", "[patterns][listenable][single]" )
{
    TestListenable obj;

    TestListenerA l1;
    TestListenerA l2;

    REQUIRE(obj.hasListeners() == false);
    REQUIRE(obj.listenerCount() == 0);

    obj.addListener(&l1);
    obj.addListener(&l2);

    REQUIRE(obj.hasListeners() == true);
    REQUIRE(obj.listenerCount() == 2);

    REQUIRE(l1.state == "");
    REQUIRE(l2.state == "");

    obj.notify();

    REQUIRE(l1.state == "called");
    REQUIRE(l2.state == "called");

    obj.removeListener(&l2);

    REQUIRE(obj.hasListeners() == true);
    REQUIRE(obj.listenerCount() == 1);

    obj.notify();

    REQUIRE(l1.state == "re-called");
    REQUIRE(l2.state == "called");
}

TEST_CASE( "Test a multiple Listenable", "[patterns][listenable][multiple]" )
{
    TestMultiListenable obj;

    TestListenerA l1;
    TestListenerA l2;
    TestListenerB l3;

    ((Listenable<TestListenerA>*)&obj)->addListener(&l1);
    ((Listenable<TestListenerA>*)&obj)->addListener(&l2);
    ((Listenable<TestListenerB>*)&obj)->addListener(&l3);

    REQUIRE(((Listenable<TestListenerA>*)&obj)->listenerCount() == 2);
    REQUIRE(((Listenable<TestListenerB>*)&obj)->listenerCount() == 1);

    TestListenerA l4;
    TestListenerB l5;

    Listenable<TestListenerA>::bind(&obj)->addListener(&l4);
    Listenable<TestListenerB>::bind(&obj)->addListener(&l5);

    REQUIRE(Listenable<TestListenerA>::bind(&obj)->listenerCount() == 3);
    REQUIRE(Listenable<TestListenerB>::bind(&obj)->listenerCount() == 2);

    TestListenerA l6;
    TestListenerB l7;

    bind<TestListenerA>(&obj)->addListener(&l6);
    bind<TestListenerB>(&obj)->addListener(&l7);

    REQUIRE(bind<TestListenerA>(&obj)->listenerCount() == 4);
    REQUIRE(bind<TestListenerB>(&obj)->listenerCount() == 3);
}
