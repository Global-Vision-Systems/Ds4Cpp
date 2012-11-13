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
 * GenericGreetProvider.cpp
 *
 *  Created on: Wed Jun 13 16:40:29 CEST 2012
 */

#include "greetdemo.GenericGreetProvider/include/GenericGreetProvider.hpp"

namespace greetdemo {

GenericGreetProvider::GenericGreetProvider() {
}

GenericGreetProvider::~GenericGreetProvider() {
}

/**
 * Activate callback, called when the component is activated.
 */
void GenericGreetProvider::activate(const std::map<std::string, std::string>& param)
{
	// const & causes problems, because I am lazy man i do a local copy
	std::map<std::string, std::string> localMap = param ;

	// Store parameters
	_lang = localMap["providedLang"] ;
	_greeting = localMap["greeting"] ;
	_defaultTarget = localMap["defaultTarget"] ;
}


std::string GenericGreetProvider::getDefaultTarget() const
{
    return _defaultTarget ;
}

std::string GenericGreetProvider::getGreeting(const std::string& who) const
{
	std::string greeting = _greeting;
	int formaterPos = greeting.find_first_of("%s") ;
	if (formaterPos != greeting.npos)
	{
		greeting = greeting.substr(0, formaterPos) + who + greeting.substr(formaterPos + 2, greeting.size() - (formaterPos + 2)) ;
	}
    return greeting ;
}

std::string GenericGreetProvider::getLang() const
{
    return _lang ;
}


} // namespace greetdemo

