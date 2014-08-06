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

#include <core/str.h>
#include <boost/algorithm/string.hpp>

using namespace Try;

String::String()
{
}

String::~String()
{
}

String::String(const char* str)
    : m_str(str)
{
}

String::String(const std::string& str)
    : m_str(str)
{
}

String::String(const String& str)
    : m_str(str.m_str)
{
}

String& String::assign(const String& str)
{
    m_str.assign(str.m_str);

    return *this;
}

String& String::trim()
{
    boost::algorithm::trim(m_str);

    return *this;
}

String& String::ltrim()
{
    boost::algorithm::trim_left(m_str);

    return *this;
}

String& String::rtrim()
{
    boost::algorithm::trim_right(m_str);

    return *this;
}

String& String::uppercase()
{
    boost::algorithm::to_upper(m_str);

    return *this;
}

String& String::lowercase()
{
    boost::algorithm::to_lower(m_str);

    return *this;
}

String& String::append(const String& str)
{
    m_str.append(str.m_str);

    return *this;
}

String& String::insert(int i, const String& str)
{
    m_str.insert(i, str.m_str.data());

    return *this;
}

String& String::insert(String::iterator& i, String::const_iterator& begin, String::const_iterator& end)
{
    m_str.insert(i, begin, end);

    return *this;
}

String& String::swap(String& str)
{
    m_str.swap(str.m_str);

    return *this;
}

String& String::clear()
{
    m_str.clear();

    return *this;
}

String& String::slice(int start, unsigned int count)
{
    unsigned int size = m_str.size();
    unsigned int pos = std::abs(start) % size;

    if (start < 0 && pos > 0)
        pos = size - pos + 1;

    if (count == 0)
        count = size;

    count = std::min(count, (size - pos));

    // Slicing is not needed if (pos == 0) and (count == size).
    if (pos != 0 || count < size)
        m_str = m_str.substr(pos, count);

    return *this;
}

String& String::operator += (const String& str)
{
    return this->append(str);
}

String::iterator String::begin()
{
    return m_str.begin();
}

String::iterator String::end()
{
    return m_str.end();
}

String::reverse_iterator String::rbegin()
{
    return m_str.rbegin();
}

String::reverse_iterator String::rend()
{
    return m_str.rend();
}


char String::operator [] (int i)
{
    return m_str[i];
}

char String::operator [] (unsigned int i)
{
    return m_str[i];
}

String::const_iterator String::begin() const
{
    return m_str.begin();
}

String::const_iterator String::end() const
{
    return m_str.end();
}

String::const_reverse_iterator String::rbegin() const
{
    return m_str.rbegin();
}

String::const_reverse_iterator String::rend() const
{
    return m_str.rend();
}

const char String::operator [] (int i) const
{
    return m_str[i];
}

const char String::operator [] (unsigned int i) const
{
    return m_str[i];
}

const char String::at(int i) const
{
    return m_str.at(i);
}

const char String::at(unsigned int i) const
{
    return m_str.at(i);
}

String String::trimmed() const
{
    return boost::algorithm::trim_copy(m_str);
}

String String::ltrimmed() const
{
    return boost::algorithm::trim_left_copy(m_str);
}

String String::rtrimmed() const
{
    return boost::algorithm::trim_right_copy(m_str);
}

String String::uppercased() const
{
    return boost::algorithm::to_upper_copy(m_str);
}

String String::lowercased() const
{
    return boost::algorithm::to_lower_copy(m_str);
}

String String::sliced(int start, unsigned int count)
{
    return String(*this).slice(start, count);
}

unsigned int String::length() const
{
    return m_str.length();
}

bool String::empty() const
{
    return m_str.empty();
}

bool String::startsWith(const String& str) const
{
    return boost::algorithm::starts_with(m_str, str);
}

bool String::endsWith(const String& str) const
{
    return boost::algorithm::ends_with(m_str, str);
}

bool String::contains(const String& str) const
{
    return boost::algorithm::contains(m_str, str);
}

String String::join(const StringList& parts) const
{
    return boost::algorithm::join(parts, m_str);
}

String String::substr(int start, int count) const
{
    return m_str.substr(start, count);
}

const char* String::c_str() const
{
    return m_str.c_str();
}

String::operator std::string () const
{
    return m_str;
}

const String String::operator + (const String& str) const
{
    return String(m_str + str.m_str);
}

bool String::operator < (const String& str) const
{
    return (m_str < str.m_str);
}

bool String::operator == (const String& str) const
{
    return (m_str == str.m_str);
}

bool String::operator != (const String& str) const
{
    return (m_str != str.m_str);
}

String String::join(const StringList& parts, const String& sep)
{
    return sep.join(parts);
}

std::ostream& operator << (std::ostream& os, const Try::String& str)
{
    os.write(str.c_str(), str.length());

    return os;
}
