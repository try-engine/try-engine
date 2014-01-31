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

#ifndef TRY_TASKSCHEDULER_H
#define TRY_TASKSCHEDULER_H

#include "task.h"
#include "singleton.h"
#include <boost/thread.hpp>

#define tasks TaskScheduler::instance()

namespace Try
{
    class TaskScheduler : public Singleton<TaskScheduler>
    {
    protected:
        unsigned int m_maxWorkerThreads;
        boost::thread_group m_workerThreads;
        mutable Mutex m_mutex;
        TaskQueue m_pendingTasks;

    public:
        TaskScheduler(unsigned int max_thread_count = boost::thread::hardware_concurrency());
        ~TaskScheduler();

        unsigned int pendingTaskCount() const;
        unsigned int maxWorkerThreadCount() const;
        unsigned int workerThreadCount() const;

        void pushTask(Task* task);
        void pushTasks(TaskQueue& ts);
        void waitAllPendingTasks();

    protected:
        void dispatchTasks();
    };
}

#endif // TRY_TASKSCHEDULER_H
