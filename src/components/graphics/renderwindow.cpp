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

#include <graphics/renderwindow.h>
#include <GLFW/glfw3.h>

using namespace Try;

RenderWindow::RenderWindowCache RenderWindow::s_cache;

RenderWindow::RenderWindow(
        const String& title,
        const ResourceHandle& camera,
        int width,
        int height,
        bool fullscreen
)
    : RenderContext("RenderWindow", camera),
      m_winHandle(0)
{
    glfwInit();

    m_winHandle = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : 0, 0);

    if (!m_winHandle)
        throw Exception("Impossible to create a Try::RenderWindow.");

    // Makes active at least one context.
    if (s_cache.empty())
        glfwMakeContextCurrent(m_winHandle);

    s_cache[m_winHandle] = this;

    glfwSetWindowCloseCallback(m_winHandle, RenderWindow::onWindowClosing);
    glfwSetWindowSizeCallback(m_winHandle, RenderWindow::onWindowResizing);

    this->setWindowTitle(title);
}

RenderWindow::~RenderWindow()
{
    s_cache.erase(m_winHandle);

    glfwDestroyWindow(m_winHandle);
    m_winHandle = 0;
}

void RenderWindow::setWindowTitle(const String& title)
{
    if (title != m_title)
    {
        glfwSetWindowTitle(m_winHandle, title.c_str());

        m_title = title;
    }
}

void RenderWindow::resize(int width, int height)
{
    glfwSetWindowSize(m_winHandle, width, height);
}

String RenderWindow::windowTitle() const
{
    return m_title;
}

int RenderWindow::width() const
{
    int width;

    glfwGetWindowSize(m_winHandle, &width, 0);

    return width;
}

int RenderWindow::height() const
{
    int height;

    glfwGetWindowSize(m_winHandle, 0, &height);

    return height;
}

double RenderWindow::getTime()
{
    return glfwGetTime();
}

void RenderWindow::onActivateContext()
{
    glfwMakeContextCurrent(m_winHandle);
}

void RenderWindow::onUpdateContext()
{
    glfwPollEvents();
    glfwSwapBuffers(m_winHandle);
}

void RenderWindow::onWindowClosing(GLFWwindow* win_handle)
{
    int ret_code = 0;

    RenderWindow* win = RenderWindow::s_cache[win_handle];

    std::vector<RenderWindowListener*> listeners = ((Listenable<RenderWindowListener>*)win)->listeners();
    int size = listeners.size();
    for (int i=0; i<size; i++)
        listeners.at(i)->onWindowClosed(win, ret_code);
}

void RenderWindow::onWindowResizing(GLFWwindow* win_handle, int width, int height)
{
    RenderWindow* win = RenderWindow::s_cache[win_handle];

    win->resizeCameraViewport(width, height);

    std::vector<RenderWindowListener*> listeners = ((Listenable<RenderWindowListener>*)win)->listeners();
    int size = listeners.size();
    for (int i=0; i<size; i++)
        listeners.at(i)->onWindowResized(win, width, height);
}
