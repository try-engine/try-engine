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

#include <input/joysticklistener.h>
#include <input/inputmanager.h>
#include <core/object.h>

using namespace Try;

PropertyName JoystickListener::name = "try.input.joysticklistener";

MessageName JoystickListener::Msg::axisMoved = "axisMoved";
MessageName JoystickListener::Msg::buttonPressed = "buttonPressed";
MessageName JoystickListener::Msg::buttonReleased = "buttonReleased";

JoystickListener::JoystickListener(Object* owner, int watched_joysticks)
    :   Property(JoystickListener::name, owner),
        m_watchedJoysticks(watched_joysticks)
{
    ((Listenable<JoystickInputListener>*)inputs)->addListener(this);
}

JoystickListener::~JoystickListener()
{
    ((Listenable<JoystickInputListener>*)inputs)->removeListener(this);
}

void JoystickListener::watchOnlyThisJoysticks(int joysticks)
{
    m_watchedJoysticks = joysticks;
}

bool JoystickListener::isWatchingJoystick(int joystick) const
{
    return (m_watchedJoysticks == Try::JoystickListener::AllJoysticks || ((1 << joystick) & m_watchedJoysticks));
}

int JoystickListener::joystickCount() const
{
    return inputs->joystickCount();
}

bool JoystickListener::isButtonPressed(int joystick, int button) const
{
    return inputs->isJoystickButtonPressed(joystick, button);
}

float JoystickListener::axisValue(int joystick, int axis) const
{
    return inputs->joystickAxisValue(joystick, axis);
}

Property* JoystickListener::copy(Object* owner) const
{
    return new JoystickListener(owner, m_watchedJoysticks);
}

void JoystickListener::onAxisMoved(int joystick, int axis, float value)
{
    if (this->isWatchingJoystick(joystick))
        this->notifyMessage(Message(JoystickListener::Msg::axisMoved, joystick, axis, value));
}

void JoystickListener::onButtonPressed(int joystick, int button)
{
    if (this->isWatchingJoystick(joystick))
        this->notifyMessage(Message(JoystickListener::Msg::buttonPressed, joystick, button));
}

void JoystickListener::onButtonReleased(int joystick, int button)
{
    if (this->isWatchingJoystick(joystick))
        this->notifyMessage(Message(JoystickListener::Msg::buttonReleased, joystick, button));
}
