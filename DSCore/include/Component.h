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
 * Component.h
 *
 *  Created on: 4 mai 2012
 *      Author: simon
 */
#ifndef COMPONENT_H_
#define COMPONENT_H_
#pragma warning( disable: 4251 )
#include <vector>
#include <list>
#include <map>
#include <string>
#include <usModule.h>
#include <usModuleContext.h>
#include "ComponentDescriptor.h"
#include "ComponentInstance.h"
#include "ComponentHandle.h"
US_USE_NAMESPACE
namespace ds4cpp
{
class US_ABI_EXPORT Component
{
    friend class ComponentManagerImpl ;

private:
    std::vector<ComponentInstance*>                     instances ;
    std::multimap<std::string, ServiceReference>        references ;
    ComponentHandle*                                    handle ;
    const Module*                                       module ;
    bool                                                satisfied ;
    ComponentInstance* newInstance() ;

    ComponentHandle* getHandle() ;

    void bindService(const std::string& interface, ServiceReference serviceObject) ;

    void unbindService(const std::string& interface, ServiceReference serviceObject) ;

    void injectAllReferences(ComponentInstance*) ;

    void injectReference(const std::string & interface, ServiceReference) ;
    void callActivate(ComponentInstance*) ;

    void publishServices(ComponentInstance*) ;

    void computeSatisfied() ;

    ComponentInstance* createInstance() ;

    Component(const Module* module, const ComponentDescriptor& descriptor) ;
    virtual ~Component() ;

public:
    const ComponentDescriptor descriptor ;
    bool isSatisfied() ;

    bool isActive() ;
} ;
}       /* namespace ds4cpp */
#endif /* COMPONENT_H_ */
