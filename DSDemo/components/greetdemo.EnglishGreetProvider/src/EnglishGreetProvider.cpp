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
 * EnglishGreetProvider.cpp
 *
 *  Created on: Wed Jun 13 16:40:29 CEST 2012
 */

#include "greetdemo.EnglishGreetProvider/include/EnglishGreetProvider.hpp"

namespace greetdemo {

EnglishGreetProvider::EnglishGreetProvider() {
}

EnglishGreetProvider::~EnglishGreetProvider() {
}

/**
 * Activate callback, called when the component is activated.
 */
void EnglishGreetProvider::activate()
{
    // leave empty if there is no need to take action on activation
}


std::string EnglishGreetProvider::getDefaultTarget() const
{
    return "world" ;
}

std::string EnglishGreetProvider::getGreeting(const std::string& who) const
{
    return "Hello " + who + "!" ;
}

std::string EnglishGreetProvider::getLang() const
{
    return "en" ;
}


} // namespace greetdemo

