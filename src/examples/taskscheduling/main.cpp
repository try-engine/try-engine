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
#include <core/taskscheduler.h>
#include <ostream>
#include <ctime>

int main(int argc, char** argv)
{
    Try::TaskScheduler ts;

    TestTask t1("Task1", 1);
    TestTask t2("Task2", 4);
    TestTask t3("Task3", 2);
    TestTask t4("Task4", 5);
    TestTask t5("Task5", 1);
    TestTask t6("Task6", 4);
    TestTask t7("Task7", 3);
    TestTask t8("Task8", 4);

    std::cout << "================================" << std::endl;
    std::cout << "Max number of worker threads: " << ts.maxWorkerThreadCount() << std::endl;
    std::cout << "================================" << std::endl;

    time_t tm = time(0);

    ts.pushTask(&t1);
    ts.pushTask(&t2);
    ts.pushTask(&t3);
    ts.pushTask(&t4);
    ts.pushTask(&t5);
    ts.pushTask(&t6);
    ts.pushTask(&t7);
    ts.pushTask(&t8);

    ts.waitAllPendingTasks();

    tm = difftime(time(0), tm);

    std::cout << "================================" << std::endl;
    std::cout << "All tasks executed in " << tm << "s." << std::endl;
    std::cout << "================================" << std::endl;

    return 0;
}
