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

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/quaternion.hpp"
#include <try.h>
#include "catch.hpp"

const float feps = 0.0001;

TEST_CASE( "Test Matrix3 invert", "[math][matrix][matrix3][invert]" )
{
    glm::mat3x3 glmm(
        3.14, 1.2, 0.5,
        3, 1, 0.2,
        0, 2, 4
    );
    Try::Matrix3 trym(
        3.14, 1.2, 0.5,
        3, 1, 0.2,
        0, 2, 4
    );

    glm::mat3x3 glmm2 = glm::inverseTranspose(glmm);
    Try::Matrix3 trym2 = trym.inverted();

    REQUIRE(abs(glmm2[0][0] - trym2.column(0)[0]) < feps);
    REQUIRE(abs(glmm2[0][1] - trym2.column(0)[1]) < feps);
    REQUIRE(abs(glmm2[0][2] - trym2.column(0)[2]) < feps);
    REQUIRE(abs(glmm2[1][0] - trym2.column(1)[0]) < feps);
    REQUIRE(abs(glmm2[1][1] - trym2.column(1)[1]) < feps);
    REQUIRE(abs(glmm2[1][2] - trym2.column(1)[2]) < feps);
    REQUIRE(abs(glmm2[2][0] - trym2.column(2)[0]) < feps);
    REQUIRE(abs(glmm2[2][1] - trym2.column(2)[1]) < feps);
    REQUIRE(abs(glmm2[2][2] - trym2.column(2)[2]) < feps);
}

TEST_CASE( "Test Matrix4 invert", "[math][matrix][matrix4][invert]" )
{
    glm::mat4x4 glmm(
        3.14, 1.2, 0.5, 0.2,
        3, 1, 0.2, 0.6,
        0, 2, 4, 1.5,
        5.2, 20, 4, 0.3
    );
    Try::Matrix4 trym(
        3.14, 1.2, 0.5, 0.2,
        3, 1, 0.2, 0.6,
        0, 2, 4, 1.5,
        5.2, 20, 4, 0.3
    );

    glm::mat4x4 glmm2 = glm::inverseTranspose(glmm);
    Try::Matrix4 trym2 = trym.inverted();

    REQUIRE(abs(glmm2[0][0] - trym2.column(0)[0]) < feps);
    REQUIRE(abs(glmm2[0][1] - trym2.column(0)[1]) < feps);
    REQUIRE(abs(glmm2[0][2] - trym2.column(0)[2]) < feps);
    REQUIRE(abs(glmm2[0][3] - trym2.column(0)[3]) < feps);
    REQUIRE(abs(glmm2[1][0] - trym2.column(1)[0]) < feps);
    REQUIRE(abs(glmm2[1][1] - trym2.column(1)[1]) < feps);
    REQUIRE(abs(glmm2[1][2] - trym2.column(1)[2]) < feps);
    REQUIRE(abs(glmm2[1][3] - trym2.column(1)[3]) < feps);
    REQUIRE(abs(glmm2[2][0] - trym2.column(2)[0]) < feps);
    REQUIRE(abs(glmm2[2][1] - trym2.column(2)[1]) < feps);
    REQUIRE(abs(glmm2[2][2] - trym2.column(2)[2]) < feps);
    REQUIRE(abs(glmm2[2][3] - trym2.column(2)[3]) < feps);
    REQUIRE(abs(glmm2[3][0] - trym2.column(3)[0]) < feps);
    REQUIRE(abs(glmm2[3][1] - trym2.column(3)[1]) < feps);
    REQUIRE(abs(glmm2[3][2] - trym2.column(3)[2]) < feps);
    REQUIRE(abs(glmm2[3][3] - trym2.column(3)[3]) < feps);
}

TEST_CASE( "Test Quaternion normalize", "[math][quaternion][normalize]" )
{
    glm::quat glmq(3.14, 1.2, 0.5, 0.2);
    Try::Quaternion tryq(3.14, 1.2, 0.5, 0.2);

    glm::quat glmqn = glm::normalize(glmq);
    Try::Quaternion tryqn = tryq.normalised();

    REQUIRE(abs(glmqn.x - tryqn.x) < feps);
    REQUIRE(abs(glmqn.y - tryqn.y) < feps);
    REQUIRE(abs(glmqn.z - tryqn.z) < feps);
    REQUIRE(abs(glmqn.w - tryqn.w) < feps);
}

TEST_CASE( "Test conversion of Quaternion from euler angles (in radians)", "[math][quaternion][from][euler angles]" )
{
    glm::quat glmq(glm::vec3(3.14, 1.2, 0.5));
    Try::Quaternion tryq(Try::Vector3(3.14, 1.2, 0.5));

    REQUIRE(abs(glmq.x - tryq.x) < feps);
    REQUIRE(abs(glmq.y - tryq.y) < feps);
    REQUIRE(abs(glmq.z - tryq.z) < feps);
    REQUIRE(abs(glmq.w - tryq.w) < feps);
}

TEST_CASE( "Test conversion of Quaternion to euler angles (in radians)", "[math][quaternion][to][euler angles]" )
{
    glm::vec3 glma(3.14, 1.2, 0.5);
    Try::Vector3 trya(3.14, 1.2, 0.5);

    glm::quat glmq(glma);
    Try::Quaternion tryq(trya);

    glm::vec3 glma2 = glm::eulerAngles(glmq);
    Try::Vector3 trya2 = tryq.toEulerAngle();

    REQUIRE(abs(glma2.x - trya2.x) < feps);
    REQUIRE(abs(glma2.y - trya2.y) < feps);
    REQUIRE(abs(glma2.z - trya2.z) < feps);
}

TEST_CASE( "Test conversion of Quaternion from a matrix 3x3", "[math][quaternion][from][matrix3]" )
{
    glm::mat3x3 glmm(
        3.14, 1.2, 0.5,
        0, 0, 0,
        0, 2, 4
    );
    Try::Matrix3 trym(
        3.14, 1.2, 0.5,
        0, 0, 0,
        0, 2, 4
    );

    glm::quat glmq(glmm);
    Try::Quaternion tryq(trym);

    REQUIRE(abs(glmq.x - tryq.x) < feps);
    REQUIRE(abs(glmq.y - tryq.y) < feps);
    REQUIRE(abs(glmq.z - tryq.z) < feps);
    REQUIRE(abs(glmq.w - tryq.w) < feps);
}

TEST_CASE( "Test conversion of Quaternion to a matrix 3x3", "[math][quaternion][to][matrix3]" )
{
    glm::mat3x3 glmm(
        3.14, 1.2, 0.5,
        0, 0, 0,
        0, 2, 4
    );
    Try::Matrix3 trym(
        3.14, 1.2, 0.5,
        0, 0, 0,
        0, 2, 4
    );

    glm::quat glmq(glmm);
    Try::Quaternion tryq(trym);

    glm::mat3x3 glmm2 = glm::mat3_cast(glmq);
    Try::Matrix3 trym2 = tryq.toMatrix();

    REQUIRE(abs(glmm2[0][0] - trym2.column(0)[0]) < feps);
    REQUIRE(abs(glmm2[0][1] - trym2.column(0)[1]) < feps);
    REQUIRE(abs(glmm2[0][2] - trym2.column(0)[2]) < feps);
    REQUIRE(abs(glmm2[1][0] - trym2.column(1)[0]) < feps);
    REQUIRE(abs(glmm2[1][1] - trym2.column(1)[1]) < feps);
    REQUIRE(abs(glmm2[1][2] - trym2.column(1)[2]) < feps);
    REQUIRE(abs(glmm2[2][0] - trym2.column(2)[0]) < feps);
    REQUIRE(abs(glmm2[2][1] - trym2.column(2)[1]) < feps);
    REQUIRE(abs(glmm2[2][2] - trym2.column(2)[2]) < feps);
}
