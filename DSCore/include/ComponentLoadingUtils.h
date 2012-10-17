//   Copyright 2012 - Global Vision Systems
//   Based on library CppMicroServices, Copyright (c) German Cancer Research Center,
//                                    Division of Medical and Biological Informatics
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
 * ComponentLoadingUtils.h
 *
 *  Created on: 15 juin 2012
 *      Author: simon
 */

#ifndef COMPONENTLOADINGUTILS_H_
#define COMPONENTLOADINGUTILS_H_

#include <usUtils_p.h>

// UNIX Defines
#if defined (US_PLATFORM_POSIX)
#define UNIX_MODULE_DIRECTORY                   "."

// WIN32
#elif defined (US_PLATFORM_WINDOWS)
#define US_RUNTIME_OUTPUT_DIRECTORY             "."
#endif


namespace ds4cpp {
namespace component {
namespace utils {


extern std::string getAbsolutePath(const std::string& name);
extern std::string getLibraryPath() ;

extern std::string prefix() ;

extern std::string suffix() ;

}
}
}


#endif /* COMPONENTLOADINGUTILS_H_ */
