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

#ifndef TRY_CORE_BASE_H
#define TRY_CORE_BASE_H

#include "rapidxml.h"
#include <boost/thread/mutex.hpp>
#include <boost/any.hpp>
#include <vector>
#include <iostream>
#include <cmath>

namespace Try
{
    const float Pi          = 3.141592654f;
    const float TwoPi       = 6.283185307f;
    const float HalfPi      = 1.570796327f;
    const float RadToDeg    = 57.29577951f;
    const float DegToRad    = 0.017453293f;
    
    const float MaxFloat    = 3.402823466e+38f;
    
    typedef boost::mutex Mutex;
    
    typedef boost::any Param;
    typedef std::vector<Param> ParamList;

    typedef rapidxml::xml_attribute<> XmlAttr;
    typedef rapidxml::xml_node<> XmlNode;
    typedef rapidxml::xml_document<> XmlDoc;
}

#endif // TRY_CORE_BASE_H
