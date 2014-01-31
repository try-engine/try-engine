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

#include "fsm.h"
#include "object.h"
#include "exception.h"

using namespace Try;

PropertyName FSM::name = "try.core.fsm";

MessageName FSM::Msg::stateAdded = "stateAdded";
MessageName FSM::Msg::stateRemoved = "stateRemoved";
MessageName FSM::Msg::stateDeleted = "stateDeleted";
MessageName FSM::Msg::stateChanging = "stateChanging";
MessageName FSM::Msg::stateChanged = "stateChanged";

FSM::FSM(Object* owner, const StateList& states)
    :   Property(FSM::name, owner),
        m_prevState(0),
        m_currentState(0),
        m_started(false)
{
    for (int i = 0; i < states.size(); i++)
        this->addState(states[i]);
}

FSM::FSM(Object* owner, State* state)
    :   Property(FSM::name, owner),
        m_prevState(0),
        m_currentState(0),
        m_started(false)
{
    this->addState(state);
}

FSM::~FSM()
{
    this->removeAllStates();
}

int FSM::stateCount() const
{
    return m_states.size();
}

State* FSM::state(const StateId& id) const
{
    if (id < m_states.size())
        return m_states.at(id);
        
    return 0;
}

State* FSM::prevState() const
{
    return this->state(m_prevState);
}

State* FSM::currentState() const
{
    return this->state(m_currentState);
}

StateId FSM::prevStateId() const
{
    return m_prevState;
}

StateId FSM::currentStateId() const
{
    return m_currentState;
}

StateId FSM::stateId(State* state) const
{
    for (int i = 0; i < m_states.size(); i++)
        if (m_states[i] == state)
            return i;
            
    return 0;
}

bool FSM::hasState(State* state) const
{
    for (int i = 0; i < m_states.size(); i++)
        if (m_states[i] == state)
            return true;
            
    return false;
}

bool FSM::hasState(const StateId& id) const
{
    if (id < m_states.size())
        return true;

    return false;
}
	
StateId FSM::addState(State* state)
{
    if (state)
    {
        if (this->hasState(state))
            return this->stateId(state);

        m_states.push_back(state);
        StateId id = m_states.size();

        state->setOwner(this);

        this->notifyMessage(Message(FSM::Msg::stateAdded, id));

        return id;
    }

    return 0;
}

void FSM::removeState(State* state)
{
    if (this->hasState(state))
    {
        StateId id = this->stateId(state);
        m_states.erase(m_states.begin()+id);
        state->setOwner(0);

        this->notifyMessage(Message(FSM::Msg::stateRemoved, id));
    }
}

void FSM::removeState(const StateId& id)
{
    if (this->hasState(id))
    {
        State* state = m_states[id];
        m_states.erase(m_states.begin()+id);
        state->setOwner(0);

        this->notifyMessage(Message(FSM::Msg::stateRemoved, id));
    }
}

void FSM::removeAllStates()
{
    for (int i = m_states.size(); i > 0; i--)
        this->removeState(i-1);
}

void FSM::deleteState(State* state)
{
    if (this->hasState(state))
    {
        StateId id = this->stateId(state);
        m_states.erase(m_states.begin()+id);
        delete state;

        this->notifyMessage(Message(FSM::Msg::stateDeleted, id));
    }
}

void FSM::deleteState(const StateId& id)
{
    if (this->hasState(id))
    {
        State* state = m_states[id];
        m_states.erase(m_states.begin()+id);
        delete state;

        this->notifyMessage(Message(FSM::Msg::stateDeleted, id));
    }
}

void FSM::deleteAllStates()
{
    for (int i = m_states.size(); i > 0; i--)
        this->deleteState(i-1);
}

bool FSM::setCurrentState(const StateId& id)
{
    State* new_state = this->state(id);
    if (!new_state)
        return false;
        
    if (m_started)
    {
        if (id == m_currentState)
            return true;

        this->notifyMessage(Message(FSM::Msg::stateChanging, id, m_currentState));

        State* old_state = this->currentState();
        if (old_state && !old_state->leave())
            return false;
                
        m_prevState = m_currentState;
    }

    if (!new_state->enter())
        return false;
        
    m_currentState = id;

    this->notifyMessage(Message(FSM::Msg::stateChanged, id, m_prevState));

    m_started = true;
    
    return true;
}

bool FSM::reset()
{
    return this->setCurrentState(0);
}

Property* FSM::copy(Object* owner) const
{
    FSM* copy = new FSM(owner);

    for (int i=0; i<this->stateCount(); i++)
        copy->addState(m_states.at(i)->copy(copy));

    return copy;
}
