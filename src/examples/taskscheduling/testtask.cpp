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

#include "testtask.h"
#include <ostream>

boost::mutex TestTask::s_mutex;
TestTask::ThreadMap TestTask::s_threadIDs;

TestTask::TestTask(const Try::String& name, int sleep)
    :   m_name(name),
        m_sleepTime(sleep)
{
}

void TestTask::doWork()
{
    s_mutex.lock();

    boost::thread::id thread_id = boost::this_thread::get_id();
    int thread_number = 0;

    if (s_threadIDs.find(thread_id) != s_threadIDs.end())
    {
        thread_number = s_threadIDs[thread_id];
    }
    else
    {
        thread_number = s_threadIDs.size();
        s_threadIDs[thread_id] = thread_number;
    }

    std::cout << "<" << m_name << "> started in thread #" << thread_number+1 << "." << std::endl;

    s_mutex.unlock();

    boost::this_thread::sleep(m_sleepTime);

    s_mutex.lock();

    std::cout << "<" << m_name << "> finished in thread #" << thread_number+1 << "." << std::endl;

    s_mutex.unlock();
}
