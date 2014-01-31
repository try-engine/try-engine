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

#ifndef TRY_MESSAGE_H
#define TRY_MESSAGE_H

#include "try.h"

namespace Try
{
    class Message
    {
    protected:
        String m_name;
        ParamList m_params;

    public:
        Message(const String& name, const Param& param);
        Message(const String& name, const Param& p1, const Param& p2);
        Message(const String& name, const Param& p1, const Param& p2, const Param& p3);
        Message(const String& name, const Param& p1, const Param& p2, const Param& p3, const Param& p4);
        Message(const String& name, const Param& p1, const Param& p2, const Param& p3, const Param& p4, const Param& p5);
        Message(const String& name, const ParamList& params = ParamList());
        virtual ~Message();

        String name() const;
        bool is(const String& name) const;

        ParamList params() const;
        int paramCount() const;
        Param param(int index = 0) const;

        template<class T>
        T param(int index = 0) const;
    };

    typedef std::vector<Message*> MessageList;
    typedef const String MessageName;

    template<class T>
    T Message::param(int index) const
    {
        return boost::any_cast<T>(this->param(index));
    }
}

#endif // TRY_MESSAGE_H
