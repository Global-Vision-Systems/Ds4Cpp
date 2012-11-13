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
#include <usLDAPFilter.h>
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
		// New incoming service 
        std::list<string> interfaces = any_cast<std::list<string> >(event.GetServiceReference().GetProperty(ServiceConstants::OBJECTCLASS())) ;
        US_INFO << "New Service : " << interfaces ;

        // For each objectClass provided by the service object
        // find the appropriate components who want it and give it
        for (auto objClassIt = interfaces.begin() ;
             objClassIt != interfaces.end() ; ++objClassIt)
        {
			// Retrieve components that has reference on the incoming service
            std::list<ComponentInstance*>* ComponentInstances = componentReferences[*objClassIt] ;

			// Valid ?
            if (ComponentInstances)
            {
                for (auto compoInstIt = ComponentInstances->begin() ;
                     compoInstIt != ComponentInstances->end() ; ++compoInstIt)
                {

					// Find the reference to know if there is a target
					for (auto referenceIt = (*compoInstIt)->getResolvedReferences().begin();
						referenceIt != (*compoInstIt)->getResolvedReferences().end(); ++referenceIt)
					{
						// Incoming service reference ?
						if (referenceIt->interface == *objClassIt)
						{
							bool bind = true ;

							// Is there a target ?
							if (!referenceIt->target.empty())
							{
								LDAPFilter filter(referenceIt->target) ;
								bind = filter.Match(event.GetServiceReference()) ;
							}

							// Filter match ? (or is empty)
							if (bind)
							{
								// Register the incoming service
								(*compoInstIt)->bindService(*objClassIt, event.GetServiceReference()) ;
								// Enable the instance ?
								enableIfSatisfied(*compoInstIt) ;
							}
						}
					}
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

	// Build the component
	Component *component = new Component(module, descriptor) ;
	this->components.push_back(component) ;     // TODO vector's thread-safety?

	// Need a factory
	if (!component->descriptor.singleton)
	{
		// Build a factory which will build component when user require it
		ComponentFactoryImplWrapper *factory = new ComponentFactoryImplWrapper(this, component) ;

		// Build the factory component and register it
		component = new Component(module, *factory->getFactoryDescriptor()) ;
		this->components.push_back(component) ;

		// Create factory instance
		ComponentInstance *factoryInstance = new ComponentInstance(component, *factory->getFactoryDescriptor()->properties) ;
		factoryInstance->set(reinterpret_cast<us::Base*>(factory)) ;
		component->factory = true ;
		component->instances.push_back(factoryInstance) ;
	}
	newComponentInstance(component) ;
}

ComponentInstance* ComponentManagerImpl::newComponentInstance(Component *component, const us::ServiceProperties& overrideProperties)
{
	ComponentInstance *instance ;
	if (!component->factory)
	{
		// Create an empty instance
		instance = component->newEmptyComponentInstance(overrideProperties) ;
	}
	else
	{
		instance = component->instances.at(0) ; // Factory are singleton
	}

	// Update component references map (for the moment it don't work with factory)
	auto        refs = instance->getResolvedReferences() ;
	for (auto it = refs.begin() ; it != refs.end() ; ++it)
	{
		if (it->interface.size() == 0)
		{
			return 0 ;
		}
		std::list<ComponentInstance*>* instances = componentReferences[it->interface] ;
		if (!instances)
		{
			instances                          = new std::list<ComponentInstance*> ;
			componentReferences[it->interface] = instances ;
		}
		instances->push_back(instance) ;
		US_DEBUG << "Adding " << component->descriptor.componentId
		<< " to references map for service " << it->interface ;
	}

	injectAvailableReferencies(instance) ;
	return instance;
}

void ComponentManagerImpl::injectAvailableReferencies(ComponentInstance* instance)
{
    // try to find services already present
	for (auto it = instance->getResolvedReferences().begin() ;
         it != instance->getResolvedReferences().end() ; ++it)
    {
		// Target filter
		std::list<ServiceReference> refs = context->GetServiceReferences(it->interface, it->target) ;

        // take first available
        for (auto it2 = refs.begin(); it2 != refs.end(); ++it2)
        {
            instance->bindService(it->interface, *it2) ;
        }
    }

    // test if component is satisfied
    enableIfSatisfied(instance) ;
}

bool ComponentManagerImpl::enableIfSatisfied(ComponentInstance* instance)
{
	Component *component = instance->getComponent() ;
	if (instance->isSatisfied())
    {
		// If it is a singleton we can only have one instance
		if ((component->descriptor.singleton && component->getNumInstance() == 1) || // Because when we create the instance it has been registered
			 component->factory || !component->descriptor.singleton)
        {
			return instance->enableInstance() ;
        }
		else
		{
			// TODO: unregister instance
		}
    }
	return false ;
}

//ComponentInstance* ComponentManagerImpl::instantiateComponent(Component* component, us::ServiceProperties *overrideProperties)
//{
//    US_INFO << " Instantiating component" ;
//    ComponentInstance* instance = component->newInstance(overrideProperties) ;
//
//    // instance can be null if newInstance failed
//    return instance ;
//}


}

/* namespace ds4cpp */
