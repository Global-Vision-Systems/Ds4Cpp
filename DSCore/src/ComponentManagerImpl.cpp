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
 * ComponentManager.cpp
 *
 *  Created on: 4 mai 2012
 *      Author: simon
 */
#include <iostream>
#include "ComponentManagerImpl.h"
US_USE_NAMESPACE
namespace ds4cpp
{
ComponentManagerImpl::ComponentManagerImpl(ModuleContext* context) : context(context), components(*new vector<Component*>())
{
    context->AddServiceListener(this,
                                &ComponentManagerImpl::handleServiceEvent) ;
}

ComponentManagerImpl::~ComponentManagerImpl()
{
    context->RemoveServiceListener(this,
                                   &ComponentManagerImpl::handleServiceEvent) ;
}

void ComponentManagerImpl::handleServiceEvent(ServiceEvent event)
{
    if (event.GetType() == ServiceEvent::REGISTERED)
    {
        std::list<string> interfaces = any_cast<std::list
                                                <string
                                                > >(event.GetServiceReference().GetProperty(
                                                        ServiceConstants::OBJECTCLASS())) ;
        US_INFO << "New Service : " << interfaces ;

        // For each objectClass provided by the service object
        // find the appropriate components who want it and give it
        for (auto objClassIt = interfaces.begin() ;
             objClassIt != interfaces.end() ; ++objClassIt)
        {
            std::list<Component*>* components = componentReferences[*objClassIt] ;
            if (components)
            {
                for (auto compoIt = components->begin() ;
                     compoIt != components->end() ; ++compoIt)
                {
                    (*compoIt)->bindService(*objClassIt,
                                            event.GetServiceReference()) ;
                    enableIfSatisfied((*compoIt)) ;
                }
            }
        }
    }
    else if (event.GetType() == ServiceEvent::UNREGISTERING)
    {
    }
}

void ComponentManagerImpl::newComponent(Module* module, const ComponentDescriptor& descriptor)
{
    US_DEBUG << "New component descriptor: " << descriptor.componentId
    << " provided by " << module->GetName() ;
    Component*  component = new Component(module, descriptor) ;
    this->components.push_back(component) ;     // TODO vector's thread-safety?
    // update component references map
    auto        refs = component->descriptor.references ;
    for (auto it = refs->begin() ; it != refs->end() ; ++it)
    {
        if (it->interface.size() == 0)
        {
            return ;
        }
        std::list<Component*>* components = componentReferences[it->interface] ;
        if (!components)
        {
            components                          = new std::list<Component*> ;
            componentReferences[it->interface]  = components ;
        }
        components->push_back(component) ;
        US_DEBUG << "Adding " << component->descriptor.componentId
        << " to references map for service " << it->interface ;
    }
    processNewComponent(component) ;
}

void ComponentManagerImpl::processNewComponent(Component* component)
{
    // try to find services already present
    for (auto it = component->descriptor.references->begin() ;
         it != component->descriptor.references->end() ; ++it)
    {
        std::list<ServiceReference> refs = context->GetServiceReferences(
            it->interface, it->target) ;

        // take first available
        for (auto it2 = refs.begin(); it2 != refs.end(); ++it2)
        {
            component->bindService(it->interface, *it2) ;
        }
    }

    // test if component is satisfied
    enableIfSatisfied(component) ;
}

bool ComponentManagerImpl::isSatisfied(Component* component)
{
    return component->isSatisfied() ;
}

void ComponentManagerImpl::enableIfSatisfied(Component* component)
{
    if (isSatisfied(component))
    {
        if (!component->isActive())
        {
            instantiateComponent(component) ;
        }
    }
}

ComponentInstance* ComponentManagerImpl::instantiateComponent(Component* component)
{
    US_INFO << " Instantiating component" ;
    ComponentInstance* instance = component->newInstance() ;

    // instance can be null if newInstance failed
    return instance ;
}
}

/* namespace ds4cpp */
