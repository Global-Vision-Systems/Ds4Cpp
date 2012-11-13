//   Copyright 2012 - Global Vision Systems
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

/*
 * ComponentLoadingUtils.cpp
 *
 *  Created on: 15 juin 2012
 *      Author: simon
 */

#include "ComponentLoadingUtils.h"


namespace ds4cpp {
namespace component {
namespace utils {

extern std::string getAbsolutePath(const std::string& name)
{
    return getLibraryPath() + "/" + prefix() + name + suffix() ;
}

extern std::string getLibraryPath()
{
#ifdef US_PLATFORM_WINDOWS

    // return std::string("/") ;
    return std::string(US_RUNTIME_OUTPUT_DIRECTORY) ;
#else
    return std::string(UNIX_MODULE_DIRECTORY) ;
#endif
}

extern std::string suffix()
{
#ifdef US_PLATFORM_WINDOWS
    return ".dll" ;
#elif defined (US_PLATFORM_APPLE)
    return ".dylib" ;
#else
    return ".so" ;
#endif
}

extern std::string prefix()
{
#if defined (US_PLATFORM_POSIX)
    return "" ; // "lib";
#else
    return "" ;
#endif
}

}
}
}

