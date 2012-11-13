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
 * ComponentInstance.cpp
 *
 *  Created on: 4 mai 2012
 *      Author: simon
 */
#include "ComponentInstance.h"
#include "Component.h"

// using namespace std;
namespace ds4cpp
{
ComponentInstance::ComponentInstance(Component *component, const us::ServiceProperties& overrideProperties) : 
component(component),
instanceObject(NULL),
satisfied(false)
{
	// Merge descriptor properties with override
	properties = *component->descriptor.properties ;
	for (us::ServiceProperties::const_iterator it = overrideProperties.begin(); it != overrideProperties.end(); ++it)
	{
		properties[it->first] = it->second ;
	}

	// Copy references and resolve target
	resolvedReferences.clear() ;
	// Loop on each descriptor reference to resolve target
	for (auto it = getComponent()->descriptor.references->begin(); it != getComponent()->descriptor.references->end(); ++it)
	{
		resolvedReferences.push_back(ComponentReference(it->name, it->interface, 
														this->replaceVariableInTarget(it->target), // Resolve ${var} here
														it->policy, it->cardinality, it->type)) ;
	}

	computeSatisfied() ;
}

ComponentInstance::~ComponentInstance()
{
	if (instanceObject)
	{
	    delete instanceObject ;
	}
}

Component* ComponentInstance::getComponent() const
{
	return component ;
}

const ::us::ServiceProperties& ComponentInstance::getProperties() const
{
	return properties ;
}

const std::vector<ComponentReference>& ComponentInstance::getResolvedReferences() const
{
	return resolvedReferences ;
}

void ComponentInstance::set(::us::Base* instance)
{
	this->instanceObject = instance ;
}

bool ComponentInstance::isValid() const
{
	return instanceObject != NULL ;
}

void ComponentInstance::bindService(const std::string& interface, us::ServiceReference serviceReference) 
{
	US_DEBUG << "Component " << component->descriptor.componentId << " was supplied a service providing interface " << interface ;

	// New incoming service, store it
	serviceReferences.insert(std::pair<std::string, us::ServiceReference>(interface, serviceReference));

	// Check if this component instance is satisfied
	computeSatisfied();

	if (isValid()) 
	{
		injectReference(interface, serviceReference);
	}
}

void ComponentInstance::unbindService(const std::string& interface, us::ServiceReference serviceReference) 
{
	for (auto it = serviceReferences.begin(); it != serviceReferences.end(); ++it) 
	{
		if (it->first == interface && it->second == serviceReference) 
		{
			serviceReferences.erase(it);
			break;
		}
	}
	computeSatisfied();
}

void ComponentInstance::computeSatisfied() 
{
	bool satis = true;

	for (auto it = resolvedReferences.begin();
			it != resolvedReferences.end(); ++it) 
	{
		if (it->type == ComponentReference::MANDATORY_REF) 
		{
			satis = satis && serviceReferences.count(it->interface) > 0;
		}
	}

	if (satis) 
	{
		if (satis == satisfied) 
		{
			US_DEBUG << component->descriptor.componentId << " is still satisfied" ;
		} 
		else 
		{
			US_INFO << component->descriptor.componentId << " is now satisfied" ;
		}
	}
	satisfied = satis;
}


bool ComponentInstance::enableInstance() 
{
	// Already enabled ?
	if (isValid() && !component->factory)
	{
		return false; 
	}

	if (!component->factory)
	{
		try 
		{
			// Call create function into wrapper
			us::Base* instanceObject = reinterpret_cast<us::Base*>(component->callCreate(this));

			// Store it
			set(instanceObject) ;
		}
		catch (std::runtime_error& e) 
		{
			US_ERROR << "Ds4C++: Error loading component file: " << e.what() ;
			return false;
		}
	}
	else
	{
		component->getHandle()->load() ;
	}

	if (isValid())
	{
		injectAllReferences();
		component->callActivate(this);
		component->publishServices(this);
		return true ;
	}
	return false;
}

void ComponentInstance::injectAllReferences() 
{
	// Loop on each references in the descriptor
	for (auto it = resolvedReferences.begin();
			it != resolvedReferences.end(); ++it) 
	{

		// Loop on each reference map
		for (auto it2 = serviceReferences.begin(); it2 != serviceReferences.end(); ++it2) 
		{
			// Is it the good interface ?
			if (it2->first != it->interface) 
			{
				continue;
			}

			// Call bind function on the module
			component->callBind(this, it2->second, it->interface, it->cardinality) ; 

			if (it->cardinality == ComponentReference::SINGLE) 
			{
				break; // stop if cardinality is single
			}
		}
	}
}

void ComponentInstance::injectReference(const std::string& interface, us::ServiceReference ref) 
{
	// Find cardinality and target
	ComponentReference::Cardinality cardinality = ComponentReference::SINGLE;

	// Look for the require interface to know the cardinality
	for (auto it = resolvedReferences.begin();
			it != resolvedReferences.end(); ++it) 
	{
		if (it->interface == interface) 
		{
			cardinality = it->cardinality;
			break;
		}
	}

	// call bind method
	component->callBind(this, ref, interface, cardinality) ;
}

bool ComponentInstance::isSatisfied() const 
{
	return this->satisfied;
}

std::string ComponentInstance::replaceVariableInTarget(std::string target)
{
	if (target.empty())
		return "" ;
	us::ServiceProperties properties = getProperties() ;
	for (int i = target.size() - 2; i >= 0; --i)
	{
		// Look for variable that look like ${var}
		// We begin by the end because we can have nested var ${var1${var2}}
		if (target[i] == '$' && target[i+1] == '{')
		{
			int variableBegin = i ;
			int variableEnd = target.find_first_of("}", variableBegin) ;
			if (variableEnd == NULL)
			{
				// Misformated target (missing '}')
				US_ERROR << "Misformated target on component " << getComponent()->descriptor.componentId ;
				return "" ;
			}
			std::string variableName = target.substr((variableBegin + 2), variableEnd - (variableBegin + 2)) ;
			std::string variableValue = "" ;
			auto it = properties.find(variableName) ;
			if (it != properties.end())
			{
				variableValue = it->second.ToString();
			}
			else
			{
				US_WARN << "Unable to find property \"" << variableName << "\" on component " << getComponent()->descriptor.componentId ;
			}

			// Replace ${var} by its value
			target = target.substr(0, variableBegin) + variableValue + target.substr((variableEnd + 1), target.size() - (variableEnd + 1)) ;

			// Do it again !
			i = target.size() - 1 ;
		}
	}
	return target ;
}
}       /* namespace ds4cpp */
