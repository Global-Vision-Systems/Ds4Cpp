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
#include "ds4cpp/ComponentManager.hpp"
US_USE_NAMESPACE
namespace ds4cpp
{
class ComponentManagerImpl : public::us::Base, public ComponentManager
{
private:
    std::vector<Component*>                                     components ;          /**< List of all the component */
    std::map<std::string, std::list<ComponentInstance*>*>       componentReferences ; /**< List of the component that has a reference on an interface */ 
    ModuleContext*                                              context ;             /**< CppMicroService module context */

friend class ComponentFactoryImpl ;

public:
    ComponentManagerImpl(ModuleContext* context) ;
    virtual ~ComponentManagerImpl() ;


	/**
	 * Remove all component created by this module
	 */
	void removeModuleComponents(Module* module) ;

	/**
	 * Remove a component with all his instance
	 */
	void removeComponent(Module* provindingModule, const ComponentDescriptor& descriptor) ;

	/**
	 * New component description
	 */
	void newComponent(Module* module, const ComponentDescriptor& descriptor) ;

	/**
	 * A component instance is leaving
	 */
	void outcomingComponentInstance(ComponentInstance *instance) ;

	/**
	 * Cpp micro service service event handler
	 */
    void handleServiceEvent(ServiceEvent event) ;

	/**
	 * Cpp micro service module event handler
	 */
    void handleModuleEvent(ModuleEvent event) ;
private:
	/**
	 * Build a new component instance
	 */
	ComponentInstance *newComponentInstance(Component* component, const us::ServiceProperties& overrideProperties = us::ServiceProperties(),
																  const us::ServiceProperties& componentParameters = us::ServiceProperties()) ;
	/**
	 * Inject the new service instance into living component instance
	 */
	void injectAvailableReferencies(ComponentInstance* instance) ;
	/**
	 * Enable the instance if it is satisfied
	 */
    bool enableIfSatisfied(ComponentInstance* instance) ;

	/**
	 * Retrieve the list of component that are listenening the service and matching with its properties
	 */
	std::list<ComponentInstance*> getInstanceListeningService(const std::string& service, const us::ServiceReference& ref) ;

	/**
	 * Retrieve the list of the components providing a service et matching with the reference target
	 */
	std::list<ComponentInstance*> getInstanceProvidingAService(const ComponentReference& reference, const std::string& requireService) ;

	/**
	 * Retrieve a valid service reference into
	 */
	bool getValidServiceRef(const std::list<ComponentInstance *>& providingInstance, const std::string& interface, us::ServiceReference currentServiceRef, us::ServiceReference& replacingServiceReference) ;
	/**
	 * Remove reference instance (interface) to the provide instance
	 */
	void referenceHasLeft(ComponentInstance *instance, const std::string& interface, const us::ServiceReference& ref) ;
} ;
}       /* namespace ds4cpp */
#endif /* COMPONENTMANAGER_H_ */
