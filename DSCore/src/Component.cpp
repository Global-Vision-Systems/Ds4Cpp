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
 * Component.cpp
 *
 *  Created on: 4 mai 2012
 *      Author: simon
 */
#include "Component.h"
#include "ComponentLoadingUtils.h"
#include <iostream>
namespace ds4cpp {

// Static functions
static std::string getCreateMethodName(const ComponentDescriptor& desc);
static std::string getBindServiceMethodName(const ComponentDescriptor& descriptor, const std::string& serviceName, const std::string& refName, ComponentReference::Cardinality cardinality, bool add = true) ;
static std::string getActivateMethodName(const ComponentDescriptor&);

ds4cpp::Component::Component(const us::Module* module, const ComponentDescriptor& descriptor) :
		module(module), descriptor(descriptor), handle(0), factory(false) 
{
}



Component::~Component() 
{
	if (handle) 
	{
		delete handle;
	}
}

ComponentHandle* Component::getHandle() 
{
	// Need to be created ?
	if (!handle) 
	{
		// Get the module path on the descript
		std::string componentPath = descriptor.implSharedObject;

		// Empty ? take module location
		if (componentPath.empty()) 
		{
			componentPath = module->GetLocation();
		} 
		else 
		{
			componentPath = ds4cpp::component::utils::getAbsolutePath(componentPath);
		}
		// Instanciate handle
		handle = new ComponentHandle(componentPath);
	}
	return handle;
}

int Component::getNumInstance() const
{
	return instances.size() ;
}

void *Component::callCreate(ComponentInstance *componentInstance)
{
	// Need to be loaded ?
	if (!getHandle()->isLoaded()) 
	{
		getHandle()->load() ;
	}

	// find create method name!
	std::string create_method_name = getCreateMethodName(descriptor);
	US_DEBUG << "Calling method named :" << create_method_name ;
	return getHandle()->createObject(create_method_name, componentInstance->getComponentParameters()) ;
}

void Component::callActivate(ComponentInstance* instance) 
{
	// Retrieve activate method name
	std::string activateMethodName = getActivateMethodName(descriptor);
	US_DEBUG << "Trying to call activate";

	// Call activate method on module
	this->handle->callActivate(activateMethodName, instance->instanceObject, instance->getProperties());
}

void Component::callBind(ComponentInstance* componentInstance, const us::ServiceReference& SvcReference, const std::string& interfaceName, const std::string& refName, ComponentReference::Cardinality cardinality)
{
	// Retrieve bind method name
	std::string bindMethodName = getBindServiceMethodName(descriptor, interfaceName, refName, cardinality) ;
	US_DEBUG << "Calling method " << bindMethodName ;

	// Retrieve us::base ptr
	us::Base* service = module->GetModuleContext()->GetService(SvcReference);

	// Call bind method on module
	this->handle->callMethod1(bindMethodName, componentInstance->instanceObject, service);
}

void Component::callUnbind(ComponentInstance* componentInstance, const us::ServiceReference& SvcReference, const std::string& interfaceName, const std::string& refName, ComponentReference::Cardinality cardinality)
{
	// Retrieve bind method name
	std::string bindMethodName = getBindServiceMethodName(descriptor, interfaceName, refName, cardinality, false) ;
	US_DEBUG << "Calling method " << bindMethodName ;

	// Retrieve us::base ptr
	us::Base* service = module->GetModuleContext()->GetService(SvcReference);

	// Call bind method on module
	this->handle->callMethod1(bindMethodName, componentInstance->instanceObject, service);
}

void Component::publishServices(ComponentInstance* componentInstance)
{
	// Publish provided services
	for (vector<double>::size_type i = 0;
			i < (*descriptor.providedServices).size(); i++) 
	{
		// Get provided service interface name
		string service = (*descriptor.providedServices)[i];

		// CppMicroService register service
		us::ServiceRegistration reg = module->GetModuleContext()->RegisterService(service.c_str(), componentInstance->instanceObject, componentInstance->getProperties());
		componentInstance->providedServiceRegistration.insert(std::pair<std::string, us::ServiceRegistration>(service, reg)) ;
	}
}

void Component::unpublishServices(ComponentInstance* componentInstance)
{
	// Unregister instance
	for (auto it = instances.begin(); it != instances.end(); ++it)
	{
		if (*it == componentInstance)
		{
			instances.erase(it) ;
			break ;
		}
	}

	// Unpublish provided services
	for (vector<double>::size_type i = 0;
			i < (*descriptor.providedServices).size(); i++) 
	{
		// Get provided service interface name
		string service = (*descriptor.providedServices)[i];

		// CppMicroService unregister with serviceref
		auto it = componentInstance->providedServiceRegistration.find(service) ;
		if (it != componentInstance->providedServiceRegistration.end())
		{
			it->second.Unregister() ;
		}
	}
}

ComponentInstance* Component::newEmptyComponentInstance(const us::ServiceProperties& overrideProperties, const us::ServiceProperties& componentParameters)
{
	// Create an empty instance and store it
	ComponentInstance *componentInstance = new ComponentInstance(this, overrideProperties, componentParameters) ;
	instances.push_back(componentInstance) ;
	return componentInstance ;
}

static std::string getCreateMethodName(const ComponentDescriptor& descriptor) 
{
	string create_method_name = "__";
	for (unsigned int i = 0; i < descriptor.componentId.size(); i++) 
	{
		char c = descriptor.componentId[i];
		if (c == ':') 
		{
			c = '_';
		}
		create_method_name.append(1, c);
	}
	create_method_name.append("__create");
	return create_method_name;
}

static std::string getActivateMethodName(const ComponentDescriptor& descriptor) 
{
	string activate_method_name = "__";
	for (unsigned int i = 0; i < descriptor.componentId.size(); i++) 
	{
		char c = descriptor.componentId[i];
		if (c == ':') 
		{
			c = '_';
		}
		activate_method_name.append(1, c);
	}
	activate_method_name.append("__activate");
	return activate_method_name;
}

static std::string getBindServiceMethodName(const ComponentDescriptor& descriptor, const std::string& serviceName, const std::string& refName, ComponentReference::Cardinality cardinality, bool add) 
{
	string bind_service_method_name = "__";
	for (unsigned int i = 0; i < descriptor.componentId.size(); i++) 
	{
		char c = descriptor.componentId[i];
		if (c == ':') 
		{
			c = '_';
		}
		bind_service_method_name.append(1, c);
	}

	bind_service_method_name.append("__");
	if (cardinality == ComponentReference::SINGLE) 
	{
		if (add)
			bind_service_method_name.append("set");
		else
			bind_service_method_name.append("unset");
	} 
	else 
	{
		if (add)
			bind_service_method_name.append("add");
		else
			bind_service_method_name.append("remove");
	}

	bind_service_method_name.append("_");
	for (unsigned int i = 0; i < serviceName.size(); i++)
	{
		char c = serviceName[i];
		if (c == ':') 
		{
			c = '_';
		}
		bind_service_method_name.append(1, c);
	}
	if (!refName.empty() && refName != serviceName)
	{
		bind_service_method_name.append("_");
		for (unsigned int i = 0; i < refName.size(); i++)
		{
			char c = refName[i];
			if (c == ':') 
			{
				c = '_';
			}
			bind_service_method_name.append(1, c);
		}
	}
	return bind_service_method_name;
}

static std::string getUnbindServiceMethodName(const ComponentDescriptor& descriptor, const std::string& serviceName, ComponentReference::Cardinality cardinality)
{
	string bind_service_method_name = "__";
	for (unsigned int i = 0; i < descriptor.componentId.size(); i++) 
	{
		char c = descriptor.componentId[i];
		if (c == ':') 
		{
			c = '_';
		}
		bind_service_method_name.append(1, c);
	}

	bind_service_method_name.append("__");
	if (cardinality == ComponentReference::SINGLE) 
	{
		bind_service_method_name.append("unset");
	} else {
		bind_service_method_name.append("remove");
	}

	bind_service_method_name.append("_");
	for (unsigned int i = 0; i < serviceName.size(); i++) 
	{
		char c = serviceName[i];
		if (c == ':') 
		{
			c = '_';
		}
		bind_service_method_name.append(1, c);
	}
	return bind_service_method_name;
}



} /* namespace ds4cpp */
