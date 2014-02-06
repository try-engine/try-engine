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

#ifndef TRY_STRING_H
#define TRY_STRING_H

#include "base.h"
#include <string>

namespace Try
{
    class String;

    typedef std::vector<String> StringList;

    class String
    {
    public:
        typedef std::string::iterator iterator;
        typedef std::string::const_iterator const_iterator;
        typedef std::string::reverse_iterator reverse_iterator;
        typedef std::string::const_reverse_iterator const_reverse_iterator;

    protected:
        std::string m_str;

    public:
        String();
        String(const char* str);
        String(const std::string& str);
        String(const String& str);
        virtual ~String();

        String& assign(const String& str);

        String& trim();
        String& ltrim();
        String& rtrim();
        String& uppercase();
        String& lowercase();

        String& append(const String& str);
        String& insert(int i, const String& str);
        String& insert(String::iterator& i, String::const_iterator& begin, String::const_iterator& end);
        String& swap(String& str);
        String& clear();
        String& slice(int start, unsigned int count = 0);

        String& operator += (const String& str);

        iterator begin();
        iterator end();
        reverse_iterator rbegin();
        reverse_iterator rend();

        char operator [] (int i);
        char operator [] (unsigned int i);

        const_iterator begin() const;
        const_iterator end() const;
        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;

        const char operator [] (int i) const;
        const char operator [] (unsigned int i) const;

        const char at(int i) const;
        const char at(unsigned int i) const;

        String trimmed() const;
        String ltrimmed() const;
        String rtrimmed() const;
        String uppercased() const;
        String lowercased() const;
        String sliced(int start, unsigned int count = 0);

        unsigned int length() const;

        bool empty() const;
        bool startsWith(const String& str) const;
        bool endsWith(const String& str) const;
        bool contains(const String& str) const;

        String join(const StringList& parts) const;
        String substr(int start, int count) const;

        const char* c_str() const;
        operator std::string () const;

        const String operator + (const String& str) const;
        bool operator < (const String& str) const;
        bool operator == (const String& str) const;
        bool operator != (const String& str) const;

        static String join(const StringList& parts, const String& sep);

        template<typename T>
        static String from(const T& src);
    };

    template<typename T>
    String String::from(const T& src)
    {
        std::stringstream buff;
        buff << src;
        return buff.str();
    }
}

std::ostream& operator << (std::ostream& os, const Try::String& str);

#endif // TRY_STRING_H
