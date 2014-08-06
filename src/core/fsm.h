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

#ifndef TRY_FSM_H
#define TRY_FSM_H

#include <core/state.h>
#include <core/listenable.h>

namespace Try
{
    class FSM;

    class FSMListener
    {
    public:
        virtual void onStarted(FSM* fsm) {}
        virtual void onStopped(FSM* fsm) {}
        virtual void onStateAdded(FSM* fsm, const StateId& state_id) {}
        virtual void onStateRemoved(FSM* fsm, const StateId& state_id) {}
        virtual void onStateDeleted(FSM* fsm, const StateId& state_id) {}
        virtual void onStateChanging(FSM* fsm, const StateId& state_id, const StateId& curr_state_id) {}
        virtual void onStateChanged(FSM* fsm, const StateId& state_id, const StateId& prev_state_id) {}
    };

    class FSM : public Listenable<FSMListener>
    {
    protected:
        StateList m_states;
        StateId m_prevState;
        StateId m_currentState;
	    
    public:
        FSM(const StateList& states = StateList());
        FSM(State* state);
        virtual ~FSM();

        int stateCount() const;

        State* state(const StateId& id) const;
        State* prevState() const;
        State* currentState() const;

        StateId prevStateId() const;
        StateId currentStateId() const;
        StateId stateId(State* state) const;

        bool hasState(const StateId& id) const;
        bool hasState(State* state) const;

        StateId addState(State* state);
        void removeState(State* state);
        void removeState(const StateId& id);
        void removeAllStates();
        void deleteState(State* state);
        void deleteState(const StateId& id);
        void deleteAllStates();

        bool setCurrentState(const StateId& id);
        bool start();
        bool reset();

        FSM* copy() const;
    };
}

#endif // TRY_FSM_H
