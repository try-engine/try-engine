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

#include <core/vector3.h>
#include <core/str.h>
#include <tests/catch.hpp>

TEST_CASE( "Test generating strings from different sources using 'from<T>(...)'", "[string][from]" )
{
    REQUIRE(Try::String::from<const char*>("Try!") == "Try!");
    REQUIRE(Try::String::from<std::string>("Try!") == "Try!");
    REQUIRE(Try::String::from<bool>(true) == "1");
    REQUIRE(Try::String::from<int>(567) == "567");
    REQUIRE(Try::String::from<float>(23.56) == "23.56");
    REQUIRE(Try::String::from<Try::Vector3>(Try::Vector3(23.56, 12, 45)) == "Vector3(23.56, 12, 45)");
}

TEST_CASE( "Test String slice", "[string][slice]" )
{
    Try::String test("Try! Engine is a very cool project...");

    test.slice(0, 34);

    REQUIRE(test == "Try! Engine is a very cool project");

    test.slice(49);

    REQUIRE(test == "a very cool project");

    test.slice(0);

    REQUIRE(test == "a very cool project");

    test.slice(-13);

    REQUIRE(test == "cool project");

    test.slice(-20);

    REQUIRE(test == "project");

    Try::String test2(test.sliced(0, 3));

    REQUIRE(test == "project");
    REQUIRE(test2 == "pro");
}
