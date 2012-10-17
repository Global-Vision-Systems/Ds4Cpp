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

#include "../include/ComponentHandle.h"
#ifndef US_PLATFORM_POSIX
#include <strsafe.h>
#endif

namespace ds4cpp
{



ComponentHandle::ComponentHandle(const std::string& name) : name(name), osHandle(0)
{
}

ComponentHandle::~ComponentHandle()
{
}

ComponentHandle* ComponentHandle::load()
{
    if (osHandle)       // already loaded
    {
        return this ;
    }
    std::string libPath = name ;
#ifdef US_PLATFORM_POSIX
    osHandle = dlopen(libPath.c_str(), RTLD_LAZY | RTLD_GLOBAL) ;
    if (!osHandle)
    {
        const char* err = dlerror() ;
        throw std::runtime_error(err ? std::string(err) : libPath) ;
    }
#else
    osHandle = LoadLibrary(libPath.c_str()) ;
    if (!osHandle)
    {
        std::string             errMsg = "Loading " ;
        std::ostringstream      oss ;
        oss << GetLastError() ;
        errMsg.append(libPath).append("failed with error: ").append(oss.str()) ;
        throw std::runtime_error(errMsg) ;
    }
#endif
    return this ;
}

void ComponentHandle::unload()
{
    if (osHandle)
    {
#ifdef US_PLATFORM_POSIX
        dlclose(osHandle) ;
#else
        FreeLibrary((HMODULE)osHandle) ;
#endif
        osHandle = 0 ;
    }
}

void* ComponentHandle::createObject(const std::string& createFunName)
{
    void* (*create)() ;
#ifdef US_PLATFORM_POSIX
    create = (void* (*)())dlsym(osHandle, createFunName.c_str()) ;
    if (!create)
    {
        const char* err = dlerror() ;
        throw std::runtime_error(err ? std::string(err) : createFunName) ;
    }
#else
    create = (void* (*)()) ::GetProcAddress((HMODULE)osHandle, createFunName.c_str()) ;
    if (!create)
    {
        std::string             errMsg = "create " ;
        std::ostringstream      oss ;
        oss << GetLastError() ;
        errMsg.append(createFunName).append("failed with error: ").append(oss.str()) ;
        throw std::runtime_error(errMsg) ;
    }
#endif
    return create() ;
}

void ComponentHandle::callMethod1(const std::string& methodName, void* instance, void* param)
{
    void (* funCallMethod1)(void*, void*) ;
#ifdef US_PLATFORM_POSIX
    funCallMethod1 = (void (*)(void*,
                               void*))dlsym(osHandle, methodName.c_str()) ;
    if (!funCallMethod1)
    {
        const char* err = dlerror() ;
        throw std::runtime_error(err ? std::string(err) : methodName) ;
    }
#else
    funCallMethod1 = (void (*)(void*, void*)) ::GetProcAddress((HMODULE)osHandle, methodName.c_str()) ;
    if (!funCallMethod1)
    {
        std::string             errMsg = "callMethod1 " ;
        std::ostringstream      oss ;
        oss << GetLastError() ;
        errMsg.append(methodName).append("failed with error: ").append(oss.str()) ;
        throw std::runtime_error(errMsg) ;
    }
#endif
    return funCallMethod1(instance, param) ;
}

void ComponentHandle::callActivate(const std::string& methodName, void* instance)
{
    void (* funActivateMethod)(void*) ;
#ifdef US_PLATFORM_POSIX
    funActivateMethod = (void (*)(void*))dlsym(osHandle, methodName.c_str()) ;
    if (!funActivateMethod)
    {
        const char* err = dlerror() ;

        // fail silently if activate isn't here!
        // TODO Log as DEBUG
        US_DEBUG << "DEBUG: " << name << ": Couldn't find activate method" ;
    }
#else
    funActivateMethod = (void (*)(void*)) ::GetProcAddress((HMODULE)osHandle, methodName.c_str()) ;
    if (!funActivateMethod)
    {
        std::string             errMsg = "callActivate " ;
        std::ostringstream      oss ;
        oss << GetLastError() ;
        errMsg.append(methodName).append("failed with error: ").append(oss.str()) ;

        // fail silently if activate isn't here!
        // TODO Log as DEBUG
        US_DEBUG << "DEBUG: " << name << " " << errMsg ;
    }
#endif
    if (funActivateMethod)
    {
        funActivateMethod(instance) ;
    }
}

}
