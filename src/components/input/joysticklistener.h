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

#ifndef TRY_JOYSTICKLISTENER_H
#define TRY_JOYSTICKLISTENER_H

#include <input/base.h>
#include <core/property.h>

namespace Try
{
    class JoystickListener :    public Property,
                                protected JoystickInputListener
    {
    public:
        static const int AllJoysticks = 0;

        static PropertyName name;

        struct Msg
        {
            static MessageName povMoved;
            static MessageName axisMoved;
            static MessageName sliderMoved;
            static MessageName buttonPressed;
            static MessageName buttonReleased;
        };

    private:
        int m_watchedJoysticks;

    public:
        JoystickListener(Object* owner, int watched_joysticks = Try::JoystickListener::AllJoysticks);
        virtual ~JoystickListener();

        void watchOnlyThisJoysticks(int joysticks);

        bool isWatchingJoystick(int joystick) const;
        int joystickCount() const;

        bool isButtonPressed(int joystick, int button) const;
        float axisValue(int joystick, int axis) const;

        Property* copy(Object* owner) const;

    protected:
        void onAxisMoved(int joystick, int axis, float value);
        void onButtonPressed(int joystick, int button);
        void onButtonReleased(int joystick, int button);
    };
}

#endif // TRY_JOYSTICKLISTENER_H
