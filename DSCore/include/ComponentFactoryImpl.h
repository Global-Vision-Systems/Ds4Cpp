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
 * ComponentFactoryImpl.h
 *
 *  Created on: 4 mai 2012
 *      Author: Lucas
 */
#ifndef COMPONENTFACTORYIMPL_H_
#define COMPONENTFACTORYIMPL_H_

#include "ds4cpp/ComponentFactory.hpp"
#include "ComponentInstance.h"
#include "ComponentDescriptor.h"

namespace ds4cpp
{
class Component ;
class ComponentManagerImpl ;

class ComponentFactoryImpl : public ComponentFactory
{
public:
	ComponentFactoryImpl(ComponentManagerImpl *componentManager, Component *buildComponent) ;
	virtual ~ComponentFactoryImpl() ;

	ComponentDescriptor *getFactoryDescriptor() const ;

	ComponentInstance *  create(const ::us::ServiceProperties& prop) ;
private:
	ComponentDescriptor  *  factoryDescriptor ;
	Component            *  buildComponent ;
	ComponentManagerImpl *  componentManager ;
};


class ComponentFactoryImplWrapper: public ::us::Base, public ComponentFactoryImpl
{
public:
	ComponentFactoryImplWrapper(ComponentManagerImpl *componentManager, Component *buildComponent) :
	ComponentFactoryImpl(componentManager, buildComponent)
	{
	}
};
} //ds4cpp

#endif //GENERICCOMPONENTFACTORY_H_
