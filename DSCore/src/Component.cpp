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
#include "../include/Component.h"
#include "../include/ComponentLoadingUtils.h"
#include <iostream>
namespace ds4cpp {
static std::string getCreateMethodName(const ComponentDescriptor& desc);

static std::string getBindServiceMethodName(const ComponentDescriptor&,
		const std::string&, ComponentReference::Cardinality);

static std::string getActivateMethodName(const ComponentDescriptor&);

ds4cpp::Component::Component(const Module* module,
		const ComponentDescriptor& descriptor) :
		module(module), descriptor(descriptor), satisfied(false), handle(0) {
	computeSatisfied();
}

void Component::bindService(const std::string& interface,
		ServiceReference serviceReference) {
	US_DEBUG << "Component " << descriptor.componentId << " was supplied a service providing interface " << interface ;
	references.insert(
			std::pair<std::string, ServiceReference>(interface,
					serviceReference));
	computeSatisfied();
	if (isActive()) {
		injectReference(interface, serviceReference);
	}
}

void Component::unbindService(const std::string& interface,
		ServiceReference serviceReference) {
	for (auto it = references.begin(); it != references.end(); ++it) {
		if (it->first == interface && it->second == serviceReference) {
			references.erase(it);
			break;
		}
	}
	computeSatisfied();
}

void Component::computeSatisfied() {
	bool satis = true;
	for (auto it = descriptor.references->begin();
			it != descriptor.references->end(); ++it) {
		if (it->type == ComponentReference::MANDATORY_REF) {
			satis = satis && references.count(it->interface) > 0;
		}
	}
	if (satis) {
		if (satis == satisfied) {
			US_DEBUG << descriptor.componentId << " is still satisfied" ;
		} else {
			US_INFO << descriptor.componentId << " is now satisfied" ;
		}
	}
	satisfied = satis;
}

Component::~Component() {
	if (handle) {
		delete handle;
	}
}

ComponentHandle* Component::getHandle() {
	if (!handle) {
		std::string componentPath = descriptor.implSharedObject;
		if (componentPath.empty()) {
			componentPath = module->GetLocation();
		} else {
			componentPath = ds4cpp::component::utils::getAbsolutePath(componentPath);
		}
		handle = new ComponentHandle(componentPath);
	}
	return handle;
}

ComponentInstance* Component::newInstance() {
	// Get component handle!
	try {
		ComponentHandle* handle = getHandle()->load();
	} catch (std::runtime_error& e) {
		US_ERROR << "Ds4C++: Error loading component file: " << e.what() ;
		return 0;
	}

	ComponentInstance* instance = createInstance();
	if (instance) {
		injectAllReferences(instance);
		callActivate(instance);
		publishServices(instance);
	}
	return instance;
}

bool Component::isActive() {
	return instances.size() > 0;
}

void Component::injectAllReferences(ComponentInstance* instance) {
	for (auto it = descriptor.references->begin();
			it != descriptor.references->end(); ++it) {
		std::string bindMethodName = getBindServiceMethodName(descriptor,
				it->interface, it->cardinality);
		for (auto it2 = references.begin(); it2 != references.end(); ++it2) {
			if (it2->first != it->interface) {
				continue;
			}
			ServiceReference ref = it2->second;
			us::Base* service = module->GetModuleContext()->GetService(ref);
			US_DEBUG << "Calling method " << bindMethodName ;
			this->handle->callMethod1(bindMethodName, instance->instanceObject,
					service);
			if (it->cardinality == ComponentReference::SINGLE) {
				break; // stop if cardinality is single
			}
		}
	}
}

void Component::injectReference(const std::string& interface,
		ServiceReference ref) {
	// Find cardinality
	ComponentReference::Cardinality cardinality = ComponentReference::SINGLE;
	for (auto it = descriptor.references->begin();
			it != descriptor.references->end(); ++it) {
		if (it->interface == interface) {
			cardinality = it->cardinality;
			break;
		}
	}
	std::string bindMethodName = getBindServiceMethodName(descriptor, interface,
			cardinality);
	us::Base* service = module->GetModuleContext()->GetService(ref);
	US_DEBUG << "Calling method " << bindMethodName ;
	for (auto it = instances.begin(); it != instances.end(); ++it) {
		auto instance = *it;
		this->handle->callMethod1(bindMethodName, instance->instanceObject,
				service);
	}
}

void Component::callActivate(ComponentInstance* instance) {
	std::string activateMethodName = getActivateMethodName(descriptor);
	US_DEBUG << "Trying to call activate";
	this->handle->callActivate(activateMethodName, instance->instanceObject);
}

void Component::publishServices(ComponentInstance* instance) {
	// publish provided services

	/*Note: (Bart) can't use C++11 range-based loop with VC++10
	 * http://blogs.msdn.com/b/vcblog/archive/2010/04/06/c-0x-core-language-features-in-vc10-the-table.aspx
	 * for (string service : *descriptor.providedServices) {
	 *      module->GetModuleContext()->RegisterService(service.c_str(),
	 *                      instance->instanceObject);
	 * }*/
	for (vector<double>::size_type i = 0;
			i < (*descriptor.providedServices).size(); i++) {
		string service = (*descriptor.providedServices)[i];
		module->GetModuleContext()->RegisterService(service.c_str(),
				instance->instanceObject);
	}
}

ComponentInstance* Component::createInstance() {
	// find create method name!
	std::string create_method_name = getCreateMethodName(descriptor);
	US_DEBUG << "Calling method named :" << create_method_name ;
	try {
		us::Base* instanceObject =
				reinterpret_cast<us::Base*>(handle->createObject(
						create_method_name));
		ComponentInstance* instance = new ComponentInstance(instanceObject);
		instances.push_back(instance);
		return instance;
	} catch (std::runtime_error& e) {
		US_ERROR << "Ds4C++: Error creating component instance: " << e.what();
	}

	return 0;
}

bool Component::isSatisfied() {
	return this->satisfied;
}

static std::string getCreateMethodName(const ComponentDescriptor& descriptor) {
	string create_method_name = "__";
	for (unsigned int i = 0; i < descriptor.componentId.size(); i++) {
		char c = descriptor.componentId[i];
		if (c == ':') {
			c = '_';
		}
		create_method_name.append(1, c);
	}
	create_method_name.append("__create");
	return create_method_name;
}

static std::string getActivateMethodName(
		const ComponentDescriptor& descriptor) {
	string activate_method_name = "__";
	for (unsigned int i = 0; i < descriptor.componentId.size(); i++) {
		char c = descriptor.componentId[i];
		if (c == ':') {
			c = '_';
		}
		activate_method_name.append(1, c);
	}
	activate_method_name.append("__activate");
	return activate_method_name;
}

static std::string getBindServiceMethodName(
		const ComponentDescriptor& descriptor, const std::string& serviceName,
		ComponentReference::Cardinality cardinality) {
	string bind_service_method_name = "__";
	for (unsigned int i = 0; i < descriptor.componentId.size(); i++) {
		char c = descriptor.componentId[i];
		if (c == ':') {
			c = '_';
		}
		bind_service_method_name.append(1, c);
	}
	bind_service_method_name.append("__");
	if (cardinality == ComponentReference::SINGLE) {
		bind_service_method_name.append("set");
	} else {
		bind_service_method_name.append("add");
	}
	bind_service_method_name.append("_");
	for (unsigned int i = 0; i < serviceName.size(); i++) {
		char c = serviceName[i];
		if (c == ':') {
			c = '_';
		}
		bind_service_method_name.append(1, c);
	}
	return bind_service_method_name;
}

static std::string getUnbindServiceMethodName(
		const ComponentDescriptor& descriptor, const std::string& serviceName,
		ComponentReference::Cardinality cardinality) {
	string bind_service_method_name = "__";
	for (unsigned int i = 0; i < descriptor.componentId.size(); i++) {
		char c = descriptor.componentId[i];
		if (c == ':') {
			c = '_';
		}
		bind_service_method_name.append(1, c);
	}
	bind_service_method_name.append("__");
	if (cardinality == ComponentReference::SINGLE) {
		bind_service_method_name.append("unset");
	} else {
		bind_service_method_name.append("remove");
	}
	bind_service_method_name.append("_");
	for (unsigned int i = 0; i < serviceName.size(); i++) {
		char c = serviceName[i];
		if (c == ':') {
			c = '_';
		}
		bind_service_method_name.append(1, c);
	}
	return bind_service_method_name;
}



} /* namespace ds4cpp */
