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
#include "testbehavior.h"
#include "testproperty1.h"
#include "testproperty2.h"

TEST_CASE( "Test a simple message sequence", "[behaviors][objects][properties][messages]" )
{
    TestBehavior tb;

    {
        Try::Object obj1("TestObject1");

        tb.watchObject(&obj1);

        TestProperty1 tp11(&obj1);
        TestProperty2 tp21(&obj1);
    }

    Try::StringList ref_logs;
    ref_logs.push_back("Received <::behaviorAdded> with 1 params from <TestObject1>.\n");

    ref_logs.push_back("Received <::addingProperty> with 1 params from <TestObject1>.\n");
    ref_logs.push_back("Received <TestProperty1::propertyAdded> with 0 params from <TestObject1>.\n");

    ref_logs.push_back("Received <TestProperty1::TestMessage1> with 2 params from <TestObject1>.\n");

    ref_logs.push_back("Received <::addingProperty> with 1 params from <TestObject1>.\n");
    ref_logs.push_back("Received <TestProperty2::propertyAdded> with 0 params from <TestObject1>.\n");

    ref_logs.push_back("Received <TestProperty2::TestMessage2> with 1 params from <TestObject1>.\n");

    ref_logs.push_back("Received <TestProperty2::removingProperty> with 0 params from <TestObject1>.\n");
    ref_logs.push_back("Received <::propertyRemoved> with 1 params from <TestObject1>.\n");

    ref_logs.push_back("Received <TestProperty1::removingProperty> with 0 params from <TestObject1>.\n");
    ref_logs.push_back("Received <::propertyRemoved> with 1 params from <TestObject1>.\n");

    ref_logs.push_back("Received <::removingBehavior> with 1 params from <TestObject1>.\n");

    REQUIRE(tb.logs() == ref_logs);
}
