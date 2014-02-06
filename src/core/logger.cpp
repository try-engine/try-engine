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

#include "logger.h"
#include <ctime>

using namespace Try;

Logger::~Logger()
{
    this->flush();
}

void Logger::log(const String& msg, LogPriority level)
{
    std::time_t t = std::time(0);
    String ts(std::ctime(&t));

    String log(ts.substr(11,8));
    log += " | ";
    log += msg;

    boost::mutex::scoped_lock lock(m_mutex);
    m_logs.push_back(Log(log, level));

    this->flush();
}

StringList Logger::logs(LogPriority max_level) const
{
    StringList logs;

    for (LogList::const_iterator it = m_logs.begin(); it < m_logs.end(); ++it)
        if (it->level <= max_level)
            logs.push_back(it->msg);

    return logs;
}

Logger::Logger()
{
    // Protected. Do nothing.
}

void Logger::flush(LogPriority max_level)
{
    for (LogList::const_iterator it = m_logs.begin(); it < m_logs.end(); ++it)
        if (it->level <= max_level)
            std::cout << it->msg << std::endl;

    m_logs.clear();
}
