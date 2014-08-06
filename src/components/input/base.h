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

#ifndef TRY_INPUTBASE_H
#define TRY_INPUTBASE_H

namespace Try
{
    class KeyboardInputListener
    {
    public:
        virtual void onKeyPressed(int key) {}
        virtual void onKeyReleased(int key) {}
    };

    class MouseInputListener
    {
    public:
        virtual void onMouseMoved(float x, float y, float nx, float ny) {}
        virtual void onMouseWheelMoved(float xoffset, float yoffset) {}
        virtual void onMouseButtonPressed(int button) {}
        virtual void onMouseButtonReleased(int button) {}
    };

    class JoystickInputListener
    {
    public:
        virtual void onJoystickAxisMoved(int joystick, int axis, float value) {}
        virtual void onJoystickButtonPressed(int joystick, int button) {}
        virtual void onJoystickButtonReleased(int joystick, int button) {}
        virtual void onJoystickCountChanged() {}
    };
}

#endif // TRY_INPUT_H
