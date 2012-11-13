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
 * GreetManagerImplWrapper.cpp
 * Wrapper for greetdemo.GreetManagerImpl
 */
#include "greetdemo.GreetManagerImpl/include/GreetManagerImpl.hpp"
#include <usBase.h>
#include <ServiceUtils.h>
#include "ComponentFactory.h"
#include <iostream>

class GreetManagerImplWrapper: public ::us::Base, public greetdemo::GreetManagerImpl
{
};

extern "C"
{
DS_ABI_EXPORT GreetManagerImplWrapper* __greetdemo__GreetManagerImpl__create()
{
	return new GreetManagerImplWrapper;
}

DS_ABI_EXPORT void __greetdemo__GreetManagerImpl__activate(GreetManagerImplWrapper* object)
{
	object->activate();
}

DS_ABI_EXPORT void __greetdemo__GreetManagerImpl__add_greetdemo__GreetProvider(GreetManagerImplWrapper* object, ::us::Base *service)
{
	greetdemo::GreetProvider* lservice = dynamic_cast<greetdemo::GreetProvider*>(service);
	object->addGreetProvider(lservice);
}

DS_ABI_EXPORT void __greetdemo__GreetManagerImpl__remove_greetdemo__GreetProvider(GreetManagerImplWrapper* object, ::us::Base *service)
{
	greetdemo::GreetProvider* lservice = dynamic_cast<greetdemo::GreetProvider*>(service);
	object->removeGreetProvider(lservice);
}

DS_ABI_EXPORT void __greetdemo__GreetManagerImpl__set_ds4cpp__ComponentFactory(GreetManagerImplWrapper* object, ::us::Base *service)
{
	ds4cpp::ComponentFactory* lservice = dynamic_cast<ds4cpp::ComponentFactory*>(service);
	object->setComponentFactory(lservice) ;
}

DS_ABI_EXPORT void __greetdemo__GreetManagerImpl__unset_ds4cpp__ComponentFactory(GreetManagerImplWrapper* object, ::us::Base *service)
{
	ds4cpp::ComponentFactory* lservice = dynamic_cast<ds4cpp::ComponentFactory*>(service);
	object->unsetComponentFactory(lservice) ;
}

} // extern "C"

