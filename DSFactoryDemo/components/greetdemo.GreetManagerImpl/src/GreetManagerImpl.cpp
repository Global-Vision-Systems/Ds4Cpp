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
 * GreetManagerImpl.cpp
 *
 *  Created on: Thu Aug 02 16:26:31 CEST 2012
 */

#include "greetdemo.GreetManagerImpl/include/GreetManagerImpl.hpp"


namespace greetdemo {

GreetManagerImpl::GreetManagerImpl() : greetProviderFactory(0) 
{
}

GreetManagerImpl::~GreetManagerImpl() 
{
}

std::string GreetManagerImpl::getDefaultTarget(const std::string& lang) const
{
    auto        providers       = this->providersByLang ;
    auto        it              = providers.find(lang) ;
    if (it == providers.end())
    {
        return "unknown lang!" ;
    }
    return it->second->getDefaultTarget() ;
}

std::string GreetManagerImpl::getGreeting(const std::string& lang, const std::string& who) const
{
    auto        providers       = this->providersByLang ;
    auto        it              = providers.find(lang) ;
    if (it == providers.end())
    {
        return "unknown lang!" ;
    }
    return it->second->getGreeting(who) ;
}

std::list<std::string> GreetManagerImpl::getAllGreetings(const std::string& who) const
{
    auto                        providers = this->providersByLang ;
    std::list<std::string>      result ;
    for (auto it = providers.begin() ; it != providers.end() ; ++it)
    {
        result.push_back(it->second->getGreeting(who)) ;
    }
    return result ;
}

void GreetManagerImpl::addGreetProvider(GreetProvider* provider)
{
    providersByLang.insert(std::make_pair(provider->getLang(), provider)) ;
}

void GreetManagerImpl::removeGreetProvider(GreetProvider* provider)
{
    providersByLang.erase(provider->getLang()) ;
}

void GreetManagerImpl::setComponentFactory(ds4cpp::ComponentFactory* factory)
{
	greetProviderFactory = factory ;
}

void GreetManagerImpl::unsetComponentFactory(ds4cpp::ComponentFactory* factory)
{
	greetProviderFactory = 0 ;
}

std::list<std::string> GreetManagerImpl::getAvailableLanguages() const
{
    auto                        providers = this->providersByLang ;
    std::list<std::string>      allLangs ;
    for (auto it = providers.begin() ; it != providers.end() ; ++it)
    {
        allLangs.push_back(it->first) ;
    }
    return allLangs ;
}

void GreetManagerImpl::activate() 
{
	if (greetProviderFactory)
	{
		// French
		us::ServiceProperties properties ;
		properties[std::string("providedLang")] = std::string("fr") ;
		properties[std::string("greeting")] = std::string("Bonjour %s !") ;
		properties[std::string("defaultTarget")] = std::string("tout le monde") ;
		greetProviderFactory->create(properties) ;

		// English
		properties.clear();
		properties[std::string("providedLang")] = std::string("en") ;
		properties[std::string("greeting")] = std::string("Hello %s !") ;
		properties[std::string("defaultTarget")] = std::string("everybody") ;
		greetProviderFactory->create(properties) ;

		// Spanish
		properties.clear();
		properties[std::string("providedLang")] = std::string("es") ;
		properties[std::string("greeting")] = std::string("Hola %s !") ;
		properties[std::string("defaultTarget")] = std::string("a todos") ;
		greetProviderFactory->create(properties) ;
	}
}

void GreetManagerImpl::reset()
{
	for (auto it = providersByLang.begin(); it != providersByLang.end(); ++it)
	{
		greetProviderFactory->remove(it->second);
		break ;
	}
}

} // namespace greetdemo


