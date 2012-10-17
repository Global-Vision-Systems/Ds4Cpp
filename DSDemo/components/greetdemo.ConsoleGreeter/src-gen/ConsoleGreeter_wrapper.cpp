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
 * ConsoleGreeterWrapper.cpp
 * Wrapper for greetdemo.ConsoleGreeter
 */
#include "greetdemo.ConsoleGreeter/include/ConsoleGreeter.hpp"
#include <usBase.h>
#include <ServiceUtils.h>

class ConsoleGreeterWrapper: public ::us::Base, public greetdemo::ConsoleGreeter
{
};

extern "C"
{
DS_ABI_EXPORT ConsoleGreeterWrapper* __greetdemo__ConsoleGreeter__create()
{
	return new ConsoleGreeterWrapper;
}

DS_ABI_EXPORT void __greetdemo__ConsoleGreeter__activate(ConsoleGreeterWrapper* object)
{
	object->activate();
}

DS_ABI_EXPORT void __greetdemo__ConsoleGreeter__set_greetdemo__GreetManager(ConsoleGreeterWrapper* object, ::us::Base *service)
{
	greetdemo::GreetManager* lservice = dynamic_cast<greetdemo::GreetManager*>(service);
	object->setGreetManager(lservice);
}

DS_ABI_EXPORT void __greetdemo__ConsoleGreeter__unset_greetdemo__GreetManager(ConsoleGreeterWrapper* object, ::us::Base *service)
{
	greetdemo::GreetManager* lservice = dynamic_cast<greetdemo::GreetManager*>(service);
	object->unsetGreetManager(lservice);
}

} // extern "C"

