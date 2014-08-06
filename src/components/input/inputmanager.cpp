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

#include <input/inputmanager.h>
#include <core/logger.h>
#include <GLFW/glfw3.h>

#define TRY_MAX_JOYSTICK_COUNT GLFW_JOYSTICK_LAST + 1

using namespace Try;

InputManager::InputManager()
    : m_connectedJoysticks(0)
{
    glfwInit();

    GLFWwindow* curr_handle = glfwGetCurrentContext();

    glfwSetKeyCallback(curr_handle, InputManager::onKeyboardKeyChanged);
    glfwSetMouseButtonCallback(curr_handle, InputManager::onMouseButtonChanged);
    glfwSetCursorPosCallback(curr_handle, InputManager::onMousePositionChanged);
    glfwSetScrollCallback(curr_handle, InputManager::onMouseWheelChanged);

    this->captureAllInput();

    logger->log("Input: init.");
}

InputManager::~InputManager()
{
    GLFWwindow* curr_handle = glfwGetCurrentContext();

    if (curr_handle)
    {
        glfwSetKeyCallback(curr_handle, 0);
        glfwSetMouseButtonCallback(curr_handle, 0);
        glfwSetCursorPosCallback(curr_handle, 0);
        glfwSetScrollCallback(curr_handle, 0);
    }

    glfwTerminate();

    logger->log("Input: released.");
}

void InputManager::captureAllInput()
{
    // Acquire keyboard and mouse status.
    glfwPollEvents();

    // Checks how many joysticks are connected.
    int count = 0;
    for (int i=0; i<TRY_MAX_JOYSTICK_COUNT; i++)
        if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GL_TRUE)
            count++;

    if (count != m_connectedJoysticks)
    {
        m_connectedJoysticks = count;
        InputManager::onJoystickCountChanged();
    }

    // Acquire joystick button and axis status.
    for (int i=0; i<m_connectedJoysticks; i++)
    {
        int num_axes = 0;
        const float* axes = glfwGetJoystickAxes(i, &num_axes);
        for (int a=0; a<num_axes; a++)
            InputManager::onJoystickAxisChanged(i, a, axes[a]);

        int num_buttons = 0;
        const unsigned char* buttons = glfwGetJoystickButtons(i, &num_buttons);
        // FIXME: This isn't correct!
        for (int b=0; b<num_buttons; b++)
            InputManager::onJoystickButtonChanged(i, b, buttons[b]);
    }
}

bool InputManager::isKeyPressed(int key) const
{
    int status = glfwGetKey(glfwGetCurrentContext(), key);
    return (status == GLFW_PRESS || status == GLFW_REPEAT);
}

bool InputManager::isMouseButtonPressed(int button) const
{
    int status = glfwGetMouseButton(glfwGetCurrentContext(), button);
    return (status == GLFW_PRESS || status == GLFW_REPEAT);
}

float InputManager::mouseX() const
{
    double x = 0;

    glfwGetCursorPos(glfwGetCurrentContext(), &x, 0);

    return x;
}

float InputManager::mouseY() const
{
    double y = 0;

    glfwGetCursorPos(glfwGetCurrentContext(), 0, &y);

    return y;
}

float InputManager::mouseXNormalized() const
{
    int width = 0;

    glfwGetWindowSize(glfwGetCurrentContext(), &width, 0);

    return (this->mouseX() / (float)width);
}

float InputManager::mouseYNormalized() const
{
    int height = 0;

    glfwGetWindowSize(glfwGetCurrentContext(), 0, &height);

    return ((height - this->mouseY()) / (float)height);
}

int InputManager::joystickCount() const
{
    return m_connectedJoysticks;
}

bool InputManager::isJoystickButtonPressed(int joystick, int button) const
{
    int num_buttons = 0;
    const unsigned char* buttons = glfwGetJoystickButtons(joystick, &num_buttons);

    if (button < num_buttons)
    {
        int status = buttons[button];
        return (status == GLFW_PRESS || status == GLFW_REPEAT);
    }

    return false;
}

float InputManager::joystickAxisValue(int joystick, int axis) const
{
    int num_axes = 0;
    const float* axes = glfwGetJoystickAxes(joystick, &num_axes);

    if (axis < num_axes)
        return axes[axis];

    return 0;
}

void InputManager::onKeyboardKeyChanged(GLFWwindow* handle, int key, int scan_code, int action, int mods)
{
    std::vector<KeyboardInputListener*> listeners = ((Listenable<KeyboardInputListener>*)inputs)->listeners();
    int size = listeners.size();

    for (int i=0; i<size; ++i)
    {
        if (action == GLFW_PRESS)
            listeners.at(i)->onKeyPressed(key);

        else if (action == GLFW_RELEASE)
            listeners.at(i)->onKeyReleased(key);
    }
}

void InputManager::onMouseButtonChanged(GLFWwindow* handle, int button, int action, int mods)
{
    std::vector<MouseInputListener*> listeners = ((Listenable<MouseInputListener>*)inputs)->listeners();
    int size = listeners.size();

    for (int i=0; i<size; ++i)
    {
        if (action == GLFW_PRESS)
            listeners.at(i)->onMouseButtonPressed(button);

        else if (action == GLFW_RELEASE)
            listeners.at(i)->onMouseButtonReleased(button);
    }
}

void InputManager::onMousePositionChanged(GLFWwindow* handle, double x, double y)
{
    // Normalization of mouse position for the current render window.
    int width, height;
    glfwGetWindowSize(handle, &width, &height);

    float nx = x / float(width);
    float ny = (height - y) / float(height);

    std::vector<MouseInputListener*> listeners = ((Listenable<MouseInputListener>*)inputs)->listeners();
    int size = listeners.size();

    for (int i=0; i<size; ++i)
        listeners.at(i)->onMouseMoved(x, y, nx, ny);
}

void InputManager::onMouseWheelChanged(GLFWwindow* handle, double xoffset, double yoffset)
{
    std::vector<MouseInputListener*> listeners = ((Listenable<MouseInputListener>*)inputs)->listeners();
    int size = listeners.size();

    for (int i=0; i<size; ++i)
        listeners.at(i)->onMouseWheelMoved(xoffset, yoffset);
}

void InputManager::onJoystickButtonChanged(int joystick, int button, int status)
{
    std::vector<JoystickInputListener*> listeners = ((Listenable<JoystickInputListener>*)inputs)->listeners();
    int size = listeners.size();

    for (int i=0; i<size; ++i)
    {
        if (status == GLFW_PRESS)
            listeners.at(i)->onJoystickButtonPressed(joystick, button);

        else if (status == GLFW_RELEASE)
            listeners.at(i)->onJoystickButtonReleased(joystick, button);
    }
}

void InputManager::onJoystickAxisChanged(int joystick, int axis, float value)
{
    std::vector<JoystickInputListener*> listeners = ((Listenable<JoystickInputListener>*)inputs)->listeners();
    int size = listeners.size();

    for (int i=0; i<size; ++i)
        listeners.at(i)->onJoystickAxisMoved(joystick, axis, value);
}

void InputManager::onJoystickCountChanged()
{
    std::vector<JoystickInputListener*> listeners = ((Listenable<JoystickInputListener>*)inputs)->listeners();
    int size = listeners.size();

    for (int i=0; i<size; ++i)
        listeners.at(i)->onJoystickCountChanged();
}
