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

struct CustomVector2
{
    float x,y;

    CustomVector2(float x, float y) : x(x), y(y) {}
};

TEST_CASE( "Test Vector2 from", "[math][vector][vector2][from]" )
{
    REQUIRE(Try::Vector2::from<CustomVector2>(CustomVector2(56, 23.824)) == Try::Vector2(56, 23.824));
    REQUIRE(Try::Vector2::from<glm::vec2>(glm::vec2(56, 23.824)) == Try::Vector2(56, 23.824));
}

TEST_CASE( "Test Vector2 dotProduct", "[math][vector][vector2][dotProduct]" )
{
    glm::vec2 glmv(34, 12.5);
    Try::Vector2 tryv(34, 12.5);

    REQUIRE(tryv.dotProduct(tryv) == glm::dot(glmv, glmv));
}

TEST_CASE( "Test Vector2 angleBetween", "[math][vector][vector2][angleBetween]" )
{
    glm::vec2 glmv(34, 12.5);
    glm::vec2 glmv2(4, 1.5);

    Try::Vector2 tryv(34, 12.5);
    Try::Vector2 tryv2(4, 1.5);

    REQUIRE(tryv.angleBetween(tryv2) == glm::angle(glm::normalize(glmv), glm::normalize(glmv2)));
}
