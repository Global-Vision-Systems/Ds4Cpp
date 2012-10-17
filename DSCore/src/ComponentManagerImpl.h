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
#include "../include/Component.h"
#include "../include/ComponentDescriptor.h"
#include "../include/ComponentInstance.h"
#include "../include/ComponentManager.h"
US_USE_NAMESPACE
namespace ds4cpp
{
class ComponentManagerImpl : public::us::Base, public ComponentManager
{
private:
    std::vector<Component*>                             components ;
    std::map<std::string, std::list<Component*>*>       componentReferences ;
    ModuleContext*                                      context ;

public:
    ComponentManagerImpl(ModuleContext* context) ;
    void newComponent(Module* module, const ComponentDescriptor& descriptor) ;

    virtual ~ComponentManagerImpl() ;
    bool isSatisfied(Component* component) ;

    void handleServiceEvent(ServiceEvent event) ;

private:
    void processNewComponent(Component* component) ;

    ComponentInstance* instantiateComponent(Component* component) ;

    void enableIfSatisfied(Component* component) ;
} ;
}       /* namespace ds4cpp */
#endif /* COMPONENTMANAGER_H_ */
