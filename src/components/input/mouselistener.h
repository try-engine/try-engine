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

#ifndef TRY_MOUSELISTENER_H
#define TRY_MOUSELISTENER_H

#include <input/base.h>
#include <core/property.h>

namespace Try
{
    class MouseListener :   public Property,
                            protected MouseInputListener
    {
    public:
        static PropertyName name;

        struct Msg
        {
            static MessageName mouseMoved;
            static MessageName mousePressed;
            static MessageName mouseReleased;
        };

        enum Buttons
        {
            MOUSE_BUTTON_1 = 0,
            MOUSE_BUTTON_2 = 1,
            MOUSE_BUTTON_3 = 2,
            MOUSE_BUTTON_4 = 3,
            MOUSE_BUTTON_5 = 4,
            MOUSE_BUTTON_6 = 5,
            MOUSE_BUTTON_7 = 6,
            MOUSE_BUTTON_8 = 7,

            // Aliases.
            MOUSE_BUTTON_LEFT = MOUSE_BUTTON_1,
            MOUSE_BUTTON_RIGHT = MOUSE_BUTTON_2,
            MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3
        };

    public:
        MouseListener(Object* owner);
        virtual ~MouseListener();

        bool isButtonPressed(int button) const;
        float x() const;
        float y() const;
        float normX() const;
        float normY() const;

        Property* copy(Object* owner) const;

    protected:
        void onMouseMoved(int x, int y);
        void onMouseButtonPressed(int button);
        void onMouseButtonReleased(int button);
    };
}

#endif // TRY_MOUSELISTENER_H
