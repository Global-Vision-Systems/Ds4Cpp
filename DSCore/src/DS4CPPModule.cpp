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
 * DS4CPPModule.cpp
 *
 *  Created on: 11 mai 2012
 *      Author: simon
 */
#include "../include/ComponentManager.h"
#include "ComponentManagerImpl.h"
#include <usModuleActivator.h>
#include <usModuleContext.h>
#include <usServiceProperties.h>

#include <usBase.h>
#include <algorithm>
#include <memory>
US_USE_NAMESPACE
using namespace ds4cpp ;
class US_ABI_LOCAL Activator : public ModuleActivator
{
private:
    void logFail()
    {
        US_ERROR << "Fatal error: could not retrieve ComponentManager service" ;
    }

    ComponentManagerImpl* componentManager ;

public:
    Activator() : componentManager(NULL)
    {
    }

    void Load(ModuleContext* context)
    {
        componentManager = new ComponentManagerImpl(context) ;
        const char* clazz = us_service_interface_iid<ComponentManager*>() ;
        context->RegisterService(clazz, this->componentManager) ;
    }

    void Unload(ModuleContext* /*context*/)
    {
    }
} ;


#include <usModuleInitialization.h>
#ifdef _DEBUG
US_EXPORT_MODULE_ACTIVATOR(DSCored, Activator)
US_INITIALIZE_MODULE("Declarative Services for C++", "DSCored", "", "1.0.0")
#else
US_EXPORT_MODULE_ACTIVATOR(DSCore, Activator)
US_INITIALIZE_MODULE("Declarative Services for C++", "DSCore", "", "1.0.0")
#endif
