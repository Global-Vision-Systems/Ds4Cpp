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
 * EnglishGreetProviderWrapper.cpp
 * Wrapper for greetdemo.EnglishGreetProvider
 */
#include "greetdemo.GenericGreetProvider/include/GenericGreetProvider.hpp"
#include <map>
#include <string>
#include <usBase.h>
#include <ServiceUtils.h>

class GenericGreetProviderWrapper: public ::us::Base, public greetdemo::GenericGreetProvider
{
};

extern "C"
{
DS_ABI_EXPORT GenericGreetProviderWrapper* __greetdemo__GenericGreetProvider__create()
{
	return new GenericGreetProviderWrapper;
}

DS_ABI_EXPORT void __greetdemo__GenericGreetProvider__activate_param(GenericGreetProviderWrapper* object, const std::map<std::string, std::string>& param)
{
	object->activate(param);
}


} // extern "C"

