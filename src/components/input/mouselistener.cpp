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

#include <input/mouselistener.h>
#include <input/inputmanager.h>
#include <core/object.h>

using namespace Try;

PropertyName MouseListener::name = "try.input.mouselistener";

MessageName MouseListener::Msg::mouseMoved = "mouseMoved";
MessageName MouseListener::Msg::mousePressed = "mousePressed";
MessageName MouseListener::Msg::mouseReleased = "mouseReleased";

MouseListener::MouseListener(Object* owner)
    :   Property(MouseListener::name, owner)
{
    ((Listenable<MouseInputListener>*)inputs)->addListener(this);
}

MouseListener::~MouseListener()
{
    ((Listenable<MouseInputListener>*)inputs)->removeListener(this);
}

bool MouseListener::isButtonPressed(int button) const
{
    return inputs->isMouseButtonPressed(button);
}

float MouseListener::x() const
{
    return inputs->mouseX();
}

float MouseListener::y() const
{
    return inputs->mouseY();
}

float MouseListener::normX() const
{
    return inputs->mouseXNormalized();
}

float MouseListener::normY() const
{
    return inputs->mouseYNormalized();
}

Property* MouseListener::copy(Object* owner) const
{
    return new MouseListener(owner);
}

void MouseListener::onMouseMoved(int x, int y)
{
    this->notifyMessage(Message(MouseListener::Msg::mouseMoved, x, y));
}

void MouseListener::onMouseButtonPressed(int button)
{
    this->notifyMessage(Message(MouseListener::Msg::mousePressed, button));
}

void MouseListener::onMouseButtonReleased(int button)
{
    this->notifyMessage(Message(MouseListener::Msg::mouseReleased, button));
}
