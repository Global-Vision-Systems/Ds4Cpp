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
 * ComponentManager.h
 *
 *  Created on: 4 mai 2012
 *      Author: simon
 */
#ifndef COMPONENTMANAGER_IMPL_H_
#define COMPONENTMANAGER_IMPL_H_
#include <usBase.h>
#include <usModule.h>
#include <usModuleContext.h>
#include <string>
#include <map>
#include <list>
#include "Component.h"
#include "ComponentDescriptor.h"
#include "ComponentInstance.h"
#include "ComponentManager.h"
US_USE_NAMESPACE
namespace ds4cpp
{
class ComponentManagerImpl : public::us::Base, public ComponentManager
{
private:
    std::vector<Component*>                                     components ;
    std::map<std::string, std::list<ComponentInstance*>*>       componentReferences ;
    ModuleContext*                                              context ;

friend class ComponentFactoryImpl ;

public:
    ComponentManagerImpl(ModuleContext* context) ;
    virtual ~ComponentManagerImpl() ;

	void newComponent(Module* module, const ComponentDescriptor& descriptor) ;

    void handleServiceEvent(ServiceEvent event) ;

private:
	ComponentInstance *newComponentInstance(Component* component, const us::ServiceProperties& overrideProperties = us::ServiceProperties()) ;

	void injectAvailableReferencies(ComponentInstance* component) ;

    bool enableIfSatisfied(ComponentInstance* instance) ;
} ;
}       /* namespace ds4cpp */
#endif /* COMPONENTMANAGER_H_ */
