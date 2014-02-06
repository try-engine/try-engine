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

#include <fsm.h>
#include "catch.hpp"

class BaseState : public Try::State
{
public:
    bool active;

public:
    BaseState() : active(false) {}

    bool enter() { active = true; return true; }
    bool leave() { active = false; return true; }
};

TEST_CASE( "Test FSM state add and remove", "[fsm][state][add][remove]" )
{
    Try::FSM fsm;

    {
        BaseState state1;
        BaseState state2;

        REQUIRE(fsm.hasState(&state1) == false);
        REQUIRE(fsm.hasState(&state2) == false);
        REQUIRE(fsm.stateCount() == 0);

        Try::StateId s1id = fsm.addState(&state1);

        REQUIRE(fsm.hasState(&state1) == true);
        REQUIRE(fsm.hasState(&state2) == false);
        REQUIRE(fsm.stateCount() == 1);
        REQUIRE(fsm.stateId(&state1) == s1id);
        REQUIRE(s1id == 1);

        Try::StateId s2id = fsm.addState(&state2);

        REQUIRE(fsm.hasState(&state1) == true);
        REQUIRE(fsm.hasState(&state2) == true);
        REQUIRE(fsm.stateCount() == 2);
        REQUIRE(fsm.stateId(&state2) == s2id);
        REQUIRE(s2id == 2);

        fsm.removeAllStates();

        REQUIRE(fsm.hasState(&state1) == false);
        REQUIRE(fsm.hasState(&state2) == false);
        REQUIRE(fsm.stateCount() == 0);

        BaseState state3;
        fsm.addState(&state3);

        REQUIRE(fsm.stateCount() == 1);

        // Here, state3 is automatically removed from FSM.
    }

    REQUIRE(fsm.stateCount() == 0);
}

TEST_CASE( "Test FSM state getting", "[fsm][state][getting]" )
{
    Try::FSM fsm;

    {
        BaseState state1;
        BaseState state2;

        Try::StateId s1id = fsm.addState(&state1);
        Try::StateId s2id = fsm.addState(&state2);

        REQUIRE(fsm.state(0) == 0);
        REQUIRE(fsm.state(s1id) == &state1);
        REQUIRE(fsm.state(s2id) == &state2);
        REQUIRE(fsm.state(456) == 0);

        // Here all states are automatically removed from FSM.
    }
}

TEST_CASE( "Test simple FSM state transition", "[fsm][state][transition]" )
{
    Try::FSM fsm;

    {
        BaseState state1;
        BaseState state2;

        fsm.addState(&state1);
        fsm.addState(&state2);

        REQUIRE(state1.active == false);
        REQUIRE(state2.active == false);
        REQUIRE(fsm.prevState() == 0);
        REQUIRE(fsm.currentState() == 0);

        fsm.start();

        REQUIRE(state1.active == true);
        REQUIRE(state2.active == false);
        REQUIRE(fsm.prevState() == 0);
        REQUIRE(fsm.currentState() == &state1);

        fsm.setCurrentState(2);

        REQUIRE(state1.active == false);
        REQUIRE(state2.active == true);
        REQUIRE(fsm.prevState() == &state1);
        REQUIRE(fsm.currentState() == &state2);

        fsm.reset();

        REQUIRE(state1.active == false);
        REQUIRE(state2.active == false);
        REQUIRE(fsm.prevState() == &state2);
        REQUIRE(fsm.currentState() == 0);

        // Here all states are automatically removed from FSM.
    }
}
