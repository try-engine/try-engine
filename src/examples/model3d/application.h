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

#ifndef TRY_MODEL3DEXAMPLE_APP_H
#define TRY_MODEL3DEXAMPLE_APP_H

#include <graphics/renderwindow.h>
#include <core/behavior.h>

namespace Try
{
    class Application : public Behavior,
                        private RenderWindowListener
    {
    private:
        int m_retCode;
        bool m_exitRequest;
        RenderWindow* m_renderWin;

    public:
        Application(RenderWindow* rw = new RenderWindow("Try! Engine - Model 3D Example"));
        virtual ~Application();

        int run();
        void exit(int ret_code = 0);

    protected:
        void onMessage(const Message& msg, Object* sender, Property* property = 0);

    private:
        void onWindowClosed(RenderWindow* rw, int ret_code);
    };
}

#endif // TRY_MODEL3DEXAMPLE_APP_H
