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

#ifndef TRY_INPUTMANAGER_H
#define TRY_INPUTMANAGER_H

#include <input/base.h>
#include <core/listenable.h>
#include <core/singleton.h>

#define inputs InputManager::instance()

class GLFWwindow;

namespace Try
{
    class InputManager : public Singleton<InputManager>,
                         public Listenable<KeyboardInputListener>,
                         public Listenable<MouseInputListener>,
                         public Listenable<JoystickInputListener>
    {
    protected:
        unsigned int m_connectedJoysticks;

    public:
        InputManager();
        virtual ~InputManager();

        void captureAllInput();

        bool isKeyPressed(int key) const;

        bool isMouseButtonPressed(int button) const;
        float mouseX() const;
        float mouseY() const;
        float mouseXNormalized() const;
        float mouseYNormalized() const;

        int joystickCount() const;
        bool isJoystickButtonPressed(int joystick, int button) const;
        float joystickAxisValue(int joystick, int axis) const;

    private:
        static void onKeyboardKeyChanged(GLFWwindow*, int, int, int, int);
        static void onMouseButtonChanged(GLFWwindow*, int, int, int);
        static void onMousePositionChanged(GLFWwindow*, double, double);
        static void onMouseWheelChanged(GLFWwindow*, double, double);
        static void onJoystickButtonChanged(int, int, int);
        static void onJoystickAxisChanged(int, int, float);
        static void onJoystickCountChanged();
    };
}

#endif // TRY_INPUTMANAGER_H
