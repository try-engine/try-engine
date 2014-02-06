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

#include "bootstrap.h"

struct CustomVector3
{
    float x,y,z;

    CustomVector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

TEST_CASE( "Test Vector3 from", "[math][vector][vector3][from]" )
{
    REQUIRE(Try::Vector3::from<CustomVector3>(CustomVector3(56, 23.824, 31.45)) == Try::Vector3(56, 23.824, 31.45));
    REQUIRE(Try::Vector3::from<glm::vec3>(glm::vec3(56, 23.824, 31.45)) == Try::Vector3(56, 23.824, 31.45));
}

TEST_CASE( "Test Vector3 dotProduct", "[math][vector][vector3][dotProduct]" )
{
    glm::vec3 glmv(34, 12.5, 5.76);
    Try::Vector3 tryv(34, 12.5, 5.76);

    REQUIRE(tryv.dotProduct(tryv) == glm::dot(glmv, glmv));
}

TEST_CASE( "Test Vector3 crossProduct", "[math][vector][vector3][crossProduct]" )
{
    glm::vec3 glmv(34, 12.5, 5.76);
    Try::Vector3 tryv(34, 12.5, 5.76);

    REQUIRE(tryv.crossProduct(tryv) == Try::Vector3::from<glm::vec3>(glm::cross(glmv, glmv)));
}

TEST_CASE( "Test Vector3 angleBetween", "[math][vector][vector3][angleBetween]" )
{
    glm::vec3 glmv(34, 12.5, 2.6);
    glm::vec3 glmv2(4, 1.5, 4.5);

    Try::Vector3 tryv(34, 12.5, 2.6);
    Try::Vector3 tryv2(4, 1.5, 4.5);

    REQUIRE(tryv.angleBetween(tryv2) == glm::angle(glm::normalize(glmv), glm::normalize(glmv2)));
}
