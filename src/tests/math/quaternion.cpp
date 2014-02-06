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

struct CustomQuaternion
{
    float x,y,z,w;

    CustomQuaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

TEST_CASE( "Test Quaternion from", "[math][vector][quaternion][from][vector4]" )
{
    REQUIRE(Try::Quaternion::from<CustomQuaternion>(CustomQuaternion(56, 23.824, 31.45, 2)) == Try::Quaternion(56, 23.824, 31.45, 2));
    REQUIRE(Try::Quaternion::from<glm::quat>(glm::quat(2, 56, 23.824, 31.45)) == Try::Quaternion(56, 23.824, 31.45, 2));
    REQUIRE(Try::Quaternion::from<Try::Vector4>(Try::Vector4(56, 23.824, 31.45, 2)) == Try::Quaternion(56, 23.824, 31.45, 2));
}

TEST_CASE( "Test Quaternion normalize", "[math][quaternion][normalize]" )
{
    glm::quat glmq(0.2, 3.14, 1.2, 0.5);
    Try::Quaternion tryq(3.14, 1.2, 0.5, 0.2);

    glm::quat glmqn = glm::normalize(glmq);
    Try::Quaternion tryqn = tryq.normalised();

    REQUIRE(fabs(glmqn.x - tryqn.x) < feps);
    REQUIRE(fabs(glmqn.y - tryqn.y) < feps);
    REQUIRE(fabs(glmqn.z - tryqn.z) < feps);
    REQUIRE(fabs(glmqn.w - tryqn.w) < feps);
}

TEST_CASE( "Test conversion of Quaternion from euler angles (in radians)", "[math][quaternion][from][euler angles]" )
{
    glm::quat glmq(glm::vec3(3.14, 1.2, 0.5));
    Try::Quaternion tryq(Try::Vector3(3.14, 1.2, 0.5));

    REQUIRE(fabs(glmq.x - tryq.x) < feps);
    REQUIRE(fabs(glmq.y - tryq.y) < feps);
    REQUIRE(fabs(glmq.z - tryq.z) < feps);
    REQUIRE(fabs(glmq.w - tryq.w) < feps);
}

TEST_CASE( "Test conversion of Quaternion to euler angles (in radians)", "[math][quaternion][to][euler angles][vector3]" )
{
    glm::vec3 glma(3.14, 1.2, 0.5);
    Try::Vector3 trya(3.14, 1.2, 0.5);

    glm::quat glmq(glma);
    Try::Quaternion tryq(trya);

    glm::vec3 glma2 = glm::eulerAngles(glmq);
    Try::Vector3 trya2 = tryq.toEulerAngle();

    REQUIRE(fabs(glma2.x - trya2.x) < feps);
    REQUIRE(fabs(glma2.y - trya2.y) < feps);
    REQUIRE(fabs(glma2.z - trya2.z) < feps);
}

TEST_CASE( "Test conversion of Quaternion from an axis and an angle", "[math][quaternion][from][axisAndAngle]" )
{
    float angle = 0.56;

    glm::vec3 glmv(3.14, 1.2, 0.5);
    Try::Vector3 tryv(3.14, 1.2, 0.5);

    glm::quat glmq = glm::angleAxis(angle, glm::normalize(glmv));
    Try::Quaternion tryq(angle, tryv);

    REQUIRE(fabs(glmq.x - tryq.x) < feps);
    REQUIRE(fabs(glmq.y - tryq.y) < feps);
    REQUIRE(fabs(glmq.z - tryq.z) < feps);
    REQUIRE(fabs(glmq.w - tryq.w) < feps);
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

    glm::quat glmq(glm::transpose(glmm));
    Try::Quaternion tryq(trym);

    REQUIRE(fabs(glmq.x - tryq.x) < feps);
    REQUIRE(fabs(glmq.y - tryq.y) < feps);
    REQUIRE(fabs(glmq.z - tryq.z) < feps);
    REQUIRE(fabs(glmq.w - tryq.w) < feps);
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

    REQUIRE(fabs(glmm2[0][0] - trym2.column(0)[0]) < feps);
    REQUIRE(fabs(glmm2[0][1] - trym2.column(0)[1]) < feps);
    REQUIRE(fabs(glmm2[0][2] - trym2.column(0)[2]) < feps);
    REQUIRE(fabs(glmm2[1][0] - trym2.column(1)[0]) < feps);
    REQUIRE(fabs(glmm2[1][1] - trym2.column(1)[1]) < feps);
    REQUIRE(fabs(glmm2[1][2] - trym2.column(1)[2]) < feps);
    REQUIRE(fabs(glmm2[2][0] - trym2.column(2)[0]) < feps);
    REQUIRE(fabs(glmm2[2][1] - trym2.column(2)[1]) < feps);
    REQUIRE(fabs(glmm2[2][2] - trym2.column(2)[2]) < feps);
}
