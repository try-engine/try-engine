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

FSM::FSM(const StateList& states)
    :   m_prevState(0),
        m_currentState(0)
{
    for (int i = 0; i < states.size(); i++)
        this->addState(states[i]);
}

FSM::FSM(State* state)
    :   m_prevState(0),
        m_currentState(0)
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
    if (id > 0 && id <= m_states.size())
        return m_states.at(id-1);
        
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
            return i+1;
            
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
    if (id > 0 && id <= m_states.size())
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

        FSM::list_type listeners = this->listeners();
        for (FSM::list_type::const_iterator it=listeners.begin(); it != listeners.end(); ++it)
            (*it)->onStateAdded(this, id);

        return id;
    }

    return 0;
}

void FSM::removeState(State* state)
{
    if (this->hasState(state))
    {
        StateId id = this->stateId(state);
        m_states.erase(m_states.begin()+id-1);
        state->setOwner(0);

        FSM::list_type listeners = this->listeners();
        for (FSM::list_type::const_iterator it=listeners.begin(); it != listeners.end(); ++it)
            (*it)->onStateRemoved(this, id);
    }
}

void FSM::removeState(const StateId& id)
{
    if (this->hasState(id))
    {
        State* state = m_states[id-1];
        m_states.erase(m_states.begin()+id-1);
        state->setOwner(0);

        FSM::list_type listeners = this->listeners();
        for (FSM::list_type::const_iterator it=listeners.begin(); it != listeners.end(); ++it)
            (*it)->onStateRemoved(this, id);
    }
}

void FSM::removeAllStates()
{
    for (int i = m_states.size(); i > 0; i--)
        this->removeState(i);
}

void FSM::deleteState(State* state)
{
    if (this->hasState(state))
    {
        StateId id = this->stateId(state);
        m_states.erase(m_states.begin()+id);
        delete state;

        FSM::list_type listeners = this->listeners();
        for (FSM::list_type::const_iterator it=listeners.begin(); it != listeners.end(); ++it)
            (*it)->onStateDeleted(this, id);
    }
}

void FSM::deleteState(const StateId& id)
{
    if (this->hasState(id))
    {
        State* state = m_states[id-1];
        m_states.erase(m_states.begin()+id-1);
        delete state;

        FSM::list_type listeners = this->listeners();
        for (FSM::list_type::const_iterator it=listeners.begin(); it != listeners.end(); ++it)
            (*it)->onStateDeleted(this, id);
    }
}

void FSM::deleteAllStates()
{
    for (int i = m_states.size(); i > 0; i--)
        this->deleteState(i);
}

bool FSM::setCurrentState(const StateId& id)
{
    FSM::list_type listeners = this->listeners();

    State* new_state = this->state(id);
    if (id && !new_state)
        return false;
        
    if (m_currentState)
    {
        if (id != m_currentState)
            for (FSM::list_type::const_iterator it=listeners.begin(); it != listeners.end(); ++it)
                (*it)->onStateChanging(this, id, m_currentState);

        State* old_state = this->currentState();
        if (old_state && !old_state->leave())
            return false;
                
        m_prevState = m_currentState;
    }

    if (new_state && !new_state->enter())
        return false;
        
    m_currentState = id;

    if (m_prevState != m_currentState)
    {
        FSM::list_type::const_iterator it;

        // Notify start.
        if (!m_prevState && m_currentState)
            for (it=listeners.begin(); it != listeners.end(); ++it)
                (*it)->onStarted(this);

        // Notify change.
        for (it=listeners.begin(); it != listeners.end(); ++it)
            (*it)->onStateChanged(this, id, m_prevState);

        // Notify stop.
        if (m_prevState && !m_currentState)
            for (it=listeners.begin(); it != listeners.end(); ++it)
                (*it)->onStopped(this);
    }
    
    return true;
}

bool FSM::start()
{
    if (this->stateCount() > 0)
        return this->setCurrentState(1);

    return false;
}

bool FSM::reset()
{
    return this->setCurrentState(0);
}

FSM* FSM::copy() const
{
    FSM* copy = new FSM();

    for (int i=0; i<this->stateCount(); i++)
        copy->addState(m_states.at(i)->copy(copy));

    return copy;
}
