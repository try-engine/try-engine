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

TEST_CASE( "Test Matrix3 from", "[math][matrix][matrix3][from]" )
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

    REQUIRE(Try::Matrix3::from<glm::mat3x3>(glmm).transposed() == trym);
}

TEST_CASE( "Test Matrix3 transpose", "[math][matrix][matrix3][transpose]" )
{
    Try::Matrix3 trym(
        3.14, 1.2, 0.5,
        3, 1, 0.2,
        0, 2, 4
    );

    Try::Matrix3 transp(trym);
    transp.transpose();

    REQUIRE(transp == trym.transposed());

    REQUIRE(transp[0][0] == trym.column(0)[0]);
    REQUIRE(transp[0][1] == trym.column(0)[1]);
    REQUIRE(transp[0][2] == trym.column(0)[2]);
    REQUIRE(transp[1][0] == trym.column(1)[0]);
    REQUIRE(transp[1][1] == trym.column(1)[1]);
    REQUIRE(transp[1][2] == trym.column(1)[2]);
    REQUIRE(transp[2][0] == trym.column(2)[0]);
    REQUIRE(transp[2][1] == trym.column(2)[1]);
    REQUIRE(transp[2][2] == trym.column(2)[2]);
}

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
    Try::Matrix3 trym2 = trym;
    trym2.invert();

    REQUIRE(trym2 == trym.inverted());

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
