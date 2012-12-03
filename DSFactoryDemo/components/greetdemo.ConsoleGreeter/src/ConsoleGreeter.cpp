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
 * ConsoleGreeter.cpp
 *
 *  Created on: Wed Jun 13 16:40:29 CEST 2012
 */

#include "greetdemo.ConsoleGreeter/include/ConsoleGreeter.hpp"
#include <iostream>
namespace greetdemo {

ConsoleGreeter::ConsoleGreeter() {
}

ConsoleGreeter::~ConsoleGreeter() {
}



void greetdemo::ConsoleGreeter::activate()
{

	// First part
    std::cout << "#################################################" << std::endl ;
    std::cout << "########## Welcome to CONSOLE GREETER ###########" << std::endl ;
    std::list<std::string>      greetings = this->greetManager->getAllGreetings(
        "GVS") ;
    for (auto it = greetings.begin() ; it != greetings.end() ; ++it)
    {
        std::cout << *it << std::endl ;
    }
    std::list<std::string>      languages = this->greetManager->getAvailableLanguages() ;
    for (auto it = languages.begin() ; it != languages.end() ; ++it)
    {
        std::cout << greetManager->getGreeting(*it, greetManager->getDefaultTarget(*it)) << std::endl ;
    }
    std::cout << "#################################################" << std::endl ;

	// Delete factory
    std::cout << "#################################################" << std::endl ;
    std::cout << "########## Delete greetProviders      ###########" << std::endl ;
	greetManager->reset() ;

	// second part
    greetings = this->greetManager->getAllGreetings("GVS") ;
    for (auto it = greetings.begin() ; it != greetings.end() ; ++it)
    {
        std::cout << *it << std::endl ;
    }
    languages = this->greetManager->getAvailableLanguages() ;
    for (auto it = languages.begin() ; it != languages.end() ; ++it)
    {
        std::cout << greetManager->getGreeting(*it, greetManager->getDefaultTarget(*it)) << std::endl ;
    }
    std::cout << "#################################################" << std::endl ;
}

/*
 * Generated bind method for service greetdemo::GreetManager
 */
void greetdemo::ConsoleGreeter::setGreetManager(GreetManager* greetManager)
{
    this->greetManager = greetManager ;
}

/*
 * Generated bind method for service greetdemo::GreetManager
 */
void ConsoleGreeter::unsetGreetManager(greetdemo::GreetManager* greetManager) {
    // TODO implement method
}


} // namespace greetdemo

