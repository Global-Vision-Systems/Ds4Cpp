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
#include "greetdemo.EnglishGreetProvider/include/EnglishGreetProvider.hpp"
#include <usBase.h>
#include <ServiceUtils.h>

class EnglishGreetProviderWrapper: public ::us::Base, public greetdemo::EnglishGreetProvider
{
};

extern "C"
{
DS_ABI_EXPORT EnglishGreetProviderWrapper* __greetdemo__EnglishGreetProvider__create()
{
	return new EnglishGreetProviderWrapper;
}

DS_ABI_EXPORT void __greetdemo__EnglishGreetProvider__activate(EnglishGreetProviderWrapper* object)
{
	object->activate();
}


} // extern "C"

