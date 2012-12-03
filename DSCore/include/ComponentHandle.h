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

#include <string>
#include <stdexcept>
#include <usUtils_p.h>
#include <usModuleRegistry.h>
#include <usModuleActivator.h>
#include <usServiceProperties.h>
#include <map>

// UNIX Defines
#if defined (US_PLATFORM_POSIX)
#define UNIX_MODULE_DIRECTORY                   "."     // TODO be smarter!
#include <dlfcn.h>

// WIN32
#elif defined (US_PLATFORM_WINDOWS)
#define US_RUNTIME_OUTPUT_DIRECTORY             "."
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <strsafe.h>
#else
#error Unsupported platform
#endif
namespace ds4cpp
{
class ComponentHandle
{
private:
    ComponentHandle(const ComponentHandle&) ;
    ComponentHandle&    operator=(const ComponentHandle&) ;

    std::string         name ;
    void*               osHandle ;

public:
    ComponentHandle(const std::string&) ;
    virtual ~ComponentHandle() ;

	bool isLoaded() const ;

    ComponentHandle* load() ;

    void* createObject(const std::string& createFunName, const ::us::ServiceProperties& componentParameters) ;

    /**
     * Call method with 1 param
     */
    void callMethod1(const std::string& methodName, void* instance, void* param) ;

    void callActivate(const std::string& methodName, void* instance, const ::us::ServiceProperties& param) ;

    void callDeactivate(const std::string& methodName, void* instance) ;

	void unload() ;

} ;


}

