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

#include "application.h"
#include <graphics/graphics.h>
#include <core/logger.h>

#define APP_INIT_MSG_NAME "app.init"
#define APP_UPDATE_MSG_NAME "app.update"
#define APP_TERMINATE_MSG_NAME "app.terminate"

using namespace Try;

Application::Application(RenderWindow* rw)
    : m_retCode(0),
      m_exitRequest(false),
      m_renderWin(rw)
{
    if (!m_renderWin)
        throw Exception("Invalid Try::RenderWindow");

    Listenable<RenderWindowListener>::bind(m_renderWin)->addListener(this);

    new GraphicsManager(m_renderWin);
}

Application::~Application()
{
    Listenable<RenderWindowListener>::bind(m_renderWin)->removeListener(this);

    delete m_renderWin;
    m_renderWin = 0;

    delete graphics;
    delete logger;
}

int Application::run()
{
    graphics->registerRenderContext(m_renderWin);

    logger->log("Application: init.");

    double last_time = RenderWindow::getTime();

    this->onMessage(Message(APP_INIT_MSG_NAME), 0);

    while (!m_exitRequest)
    {
        double current_time = RenderWindow::getTime();
        double dt = current_time - last_time;

        this->onMessage(Message(APP_UPDATE_MSG_NAME, dt), 0);

        last_time = current_time;
    }

    this->onMessage(Message(APP_TERMINATE_MSG_NAME), 0);

    graphics->unregisterRenderContext(m_renderWin);

    logger->log("Application: closed.");

    return m_retCode;
}

void Application::exit(int ret_code)
{
    if (!m_exitRequest)
    {
        m_retCode = ret_code;
        m_exitRequest = true;
    }
}

void Application::onMessage(const Message& msg, Object* sender, Property* property)
{
    if (!sender)
    {
        if (msg.is(APP_INIT_MSG_NAME))
        {
            // Set a camera to render the scene...
            TransformableHandle cam = graphics->loadCamera(
                "Default Cam",
                "pipelines/forward.pipeline.xml",
                m_renderWin->width(),
                m_renderWin->height()
            );

            m_renderWin->setActiveCamera(cam);

            // ...then add a model...
            Object* man = new Object("Man");
            Model3D* man_model = new Model3D(man, "models/man/man.scene.xml");
            man_model->addAnimation("animations/man.anim");
            man_model->runAnimation(0, 10);
            man_model->setPosition(Vector3(0, -0.8, -3));

            // ...and also a light.
            Object* light = new Object("Light");
            LightEmitter* light_emitter = new LightEmitter(light, light->name());
            light_emitter->setPosition(Vector3(0, 20, 50));

            this->watchObject(man);
            this->watchObject(light);
        }

        else if (msg.is(APP_UPDATE_MSG_NAME))
        {
            double dt = msg.param<double>();

            graphics->renderOneFrame(dt);
        }

        else if (msg.is(APP_TERMINATE_MSG_NAME))
        {
            this->deleteAllObjects();
        }
    }
}

void Application::onWindowClosed(RenderWindow* rw, int ret_code)
{
    if (rw == m_renderWin)
        this->exit(ret_code);
}
