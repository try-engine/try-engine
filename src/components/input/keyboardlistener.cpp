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

#include <input/keyboardlistener.h>
#include <input/inputmanager.h>
#include <core/object.h>

using namespace Try;

PropertyName KeyboardListener::name = "try.input.keyboardlistener";

MessageName KeyboardListener::Msg::keyPressed = "keyPressed";
MessageName KeyboardListener::Msg::keyReleased = "keyReleased";

KeyboardListener::KeyboardListener(Object* owner)
    :   Property(KeyboardListener::name, owner)
{
    ((Listenable<KeyboardInputListener>*)inputs)->addListener(this);
}

KeyboardListener::~KeyboardListener()
{
    ((Listenable<KeyboardInputListener>*)inputs)->removeListener(this);
}

bool KeyboardListener::isKeyPressed(int key) const
{
    return inputs->isKeyPressed(key);
}

Property* KeyboardListener::copy(Object* owner) const
{
    return new KeyboardListener(owner);
}

void KeyboardListener::onKeyPressed(int key)
{
    this->notifyMessage(Message(KeyboardListener::Msg::keyPressed, key));
}

void KeyboardListener::onKeyReleased(int key)
{
    this->notifyMessage(Message(KeyboardListener::Msg::keyReleased, key));
}
