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
 * ComponentFactory.h
 *
 *  Created on: 4 mai 2012
 *      Author: Lucas
 */
#ifndef COMPONENTFACTORY_H_
#define COMPONENTFACTORY_H_

#include "usServiceProperties.h"
#include <ComponentInstance.h>

#define DS4CPP_FACTORY_SERVICE_NAME           std::string("ds4cpp::ComponentFactory")
#define DS4CPP_FACTORY_COMPONENT_NAME         std::string("component.name")
#define DS4CPP_FACTORY_PROVIDED_SERVICE_NAME  std::string("component.services")

namespace ds4cpp
{
class ComponentFactory
{
public:
	virtual const us::ServiceProperties& getFactoryProperties() const = 0 ;

	std::vector<std::string> getComponentProvidedServices() const
	{
		return us::any_cast<std::vector<std::string> >(getFactoryProperties().at(DS4CPP_FACTORY_PROVIDED_SERVICE_NAME))  ;
	}

	std::string getComponentName() const
	{
		return us::any_cast<std::string>(getFactoryProperties().at(DS4CPP_FACTORY_COMPONENT_NAME)) ;
	}

	/**
	 * Create a new instancy
	 * @param[in] serviceProperties provided service properties
	 * @param[in] componentParameters component parameters that will be given to the constructor
	 */
	virtual ComponentInstance *          create(const ::us::ServiceProperties& serviceProperties = us::ServiceProperties(),
		                                       const ::us::ServiceProperties& componentParameters = us::ServiceProperties()) = 0 ;

	template <class T>
	bool remove(T *objClass)
	{
		return _remove(dynamic_cast<us::Base*>(objClass)) ;
	}
	virtual bool                         _remove(us::Base *instanceObjectPtr) = 0 ;

};
}

#endif // COMPONENTFACTORY_H_