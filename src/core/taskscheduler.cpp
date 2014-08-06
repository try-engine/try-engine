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

#include <core/taskscheduler.h>

using namespace Try;

TaskScheduler::TaskScheduler(unsigned int max_thread_count)
    :   m_maxWorkerThreads(std::min(max_thread_count, boost::thread::hardware_concurrency()))
{
}

TaskScheduler::~TaskScheduler()
{
    this->waitAllPendingTasks();
}

unsigned int TaskScheduler::pendingTaskCount() const
{
    return m_pendingTasks.size();
}

unsigned int TaskScheduler::maxWorkerThreadCount() const
{
    return m_maxWorkerThreads;
}

unsigned int TaskScheduler::workerThreadCount() const
{
    return m_workerThreads.size();
}

void TaskScheduler::pushTask(Task* task)
{
    boost::mutex::scoped_lock lock(m_mutex);

    m_pendingTasks.push(task);

    lock.unlock();

    if (m_workerThreads.size() < m_maxWorkerThreads)
        m_workerThreads.create_thread(boost::bind(&TaskScheduler::dispatchTasks, this));
}

void TaskScheduler::pushTasks(TaskQueue& ts)
{
    while (!ts.empty())
    {
        this->pushTask(ts.front());
        ts.pop();
    }
}

void TaskScheduler::waitAllPendingTasks()
{
    m_workerThreads.join_all();
}

void TaskScheduler::dispatchTasks()
{
    while (!m_pendingTasks.empty())
    {
        boost::mutex::scoped_lock lock(m_mutex);

        Task* task = m_pendingTasks.front();
        m_pendingTasks.pop();

        lock.unlock();

        task->execute();
    }
}
