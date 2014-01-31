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

#ifndef LOGGER_H
#define LOGGER_H

#include "singleton.h"

#define logger Try::Logger::instance()

namespace  Try
{
    class Logger : public Singleton<Logger>
    {
    public:
        enum LogPriority
        {
            Critical,
            Normal,
            Verbose,
            Debug,
            All = 9999
        };

    protected:
        struct Log
        {
            String msg;
            LogPriority level;

            Log(const String& msg, LogPriority level) : msg(msg), level(level) {}
        };

        typedef std::vector<Log> LogList;

        Mutex m_mutex;
        LogList m_logs;

    public:
        ~Logger();

        void log(const String& msg, LogPriority level = Logger::Normal);

        StringList logs(LogPriority max_level = Logger::All) const;

    protected:
        Logger();

        void flush(LogPriority max_level = Logger::All);
    };
}

#endif // LOGGER_H
