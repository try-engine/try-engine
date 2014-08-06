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

#ifndef TRY_RENDERWINDOW_H
#define TRY_RENDERWINDOW_H

#include <graphics/rendercontext.h>

class GLFWwindow;

namespace Try
{
    class RenderWindow : public RenderContext,
                         public Listenable<RenderWindowListener>
    {
    private:
        typedef std::map<GLFWwindow*, RenderWindow*> RenderWindowCache;

        String m_title;
        GLFWwindow* m_winHandle;

        static RenderWindowCache s_cache;

    public:
        RenderWindow(
            const String& title = "Try! Engine",
            const ResourceHandle& camera = 0,
            int width = 800,
            int height = 600,
            bool fullscreen = false
        );
        virtual ~RenderWindow();

        void setWindowTitle(const String& title);
        void resize(int width, int height);

        String windowTitle() const;
        int width() const;
        int height() const;

        static double getTime();

    protected:
        void onActivateContext();
        void onUpdateContext();

        static void onWindowClosing(GLFWwindow*);
        static void onWindowResizing(GLFWwindow*, int, int);
    };
}

#endif // TRY_RENDERWINDOW_H
