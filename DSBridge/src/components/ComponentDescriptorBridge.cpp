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
 *
 *  Created on: 10 mai 2012
 *      Author: simon
 */
#include <iostream>
#include <ds4cpp/ComponentManager.hpp>
#include <ComponentDescriptor.h>
#include "../../include/ComponentProvider.h"
namespace ds4cpp
{
class ComponentDescriptorBridge
{
private:
    ComponentManager* componentManager ;

public:
    ComponentDescriptorBridge() : componentManager(NULL)
    {
    }

    virtual ~ComponentDescriptorBridge()
    {
    }

    void setComponentManager(ComponentManager*) ;

    void addComponentProvider(ComponentProvider*) ;

    void removeComponentProvider(ComponentProvider*) ;
} ;

void ComponentDescriptorBridge::setComponentManager(ComponentManager* componentManager)
{
    this->componentManager = componentManager ;
}

void ComponentDescriptorBridge::addComponentProvider(ComponentProvider* provider)
{
    std::vector<ComponentDescriptor*>* descriptors = provider->getComponentDescriptors() ;
    for (unsigned int i = 0 ; i < descriptors->size() ; i++)
    {
        ComponentDescriptor* desc = descriptors->at(i) ;
        componentManager->newComponent(provider->getProvider(), *desc) ;
    }
}

void ComponentDescriptorBridge::removeComponentProvider(ComponentProvider* provider)
{
    std::vector<ComponentDescriptor*>* descriptors = provider->getComponentDescriptors() ;
    for (unsigned int i = 0 ; i < descriptors->size() ; i++)
    {
        ComponentDescriptor* desc = descriptors->at(i) ;
        componentManager->removeComponent(provider->getProvider(), *desc) ;
    }	
}
}
