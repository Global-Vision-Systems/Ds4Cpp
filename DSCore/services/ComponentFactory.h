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

#define DS4CPP_FACTORY_SERVICE_NAME    std::string("ds4cpp::ComponentFactory")
#define DS4CPP_FACTORY_COMPONENT_NAME  std::string("component.name")

namespace ds4cpp
{
class ComponentFactory
{
public:
	virtual ComponentInstance *  create(const ::us::ServiceProperties& prop) = 0 ;
};
}

#endif // COMPONENTFACTORY_H_