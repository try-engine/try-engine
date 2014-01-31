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

#include "message.h"

using namespace Try;

Message::Message(const String& name, const Param& param)
    :   m_name(name)
{
    m_params.push_back(param);
}

Message::Message(const String& name, const Param& p1, const Param& p2)
    :   m_name(name)
{
    m_params.push_back(p1);
    m_params.push_back(p2);
}

Message::Message(const String& name, const Param& p1, const Param& p2, const Param& p3)
    :   m_name(name)
{
    m_params.push_back(p1);
    m_params.push_back(p2);
    m_params.push_back(p3);
}

Message::Message(const String& name, const Param& p1, const Param& p2, const Param& p3, const Param& p4)
    :   m_name(name)
{
    m_params.push_back(p1);
    m_params.push_back(p2);
    m_params.push_back(p3);
    m_params.push_back(p4);
}

Message::Message(const String& name, const Param& p1, const Param& p2, const Param& p3, const Param& p4, const Param& p5)
    :   m_name(name)
{
    m_params.push_back(p1);
    m_params.push_back(p2);
    m_params.push_back(p3);
    m_params.push_back(p4);
    m_params.push_back(p5);
}

Message::Message(const String& name, const ParamList& params)
    :   m_name(name),
        m_params(params)
{
}

Message::~Message()
{
}

String Message::name() const
{
    return m_name;
}

bool Message::is(const String& name) const
{
    return (m_name == name);
}

ParamList Message::params() const
{
    return m_params;
}

int Message::paramCount() const
{
    return m_params.size();
}

Param Message::param(int index) const
{
    if (index > -1 && index < this->paramCount())
        return m_params[index];

    return Param();
}
