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
 * GreetManagerImpl.hpp
 * Component greetdemo.GreetManagerImpl
 * Created on: Wed Jun 13 16:40:29 CEST 2012
 */

#ifndef GREETDEMO_GREETMANAGERIMPL_H_
#define GREETDEMO_GREETMANAGERIMPL_H_

#include <string>
#include <list>
#include <map>
#include <greetdemo/GreetProvider.hpp>
#include <greetdemo/GreetManager.hpp>
#include <ds4cpp/ComponentFactory.hpp>

namespace greetdemo {

class GreetManagerImpl: public greetdemo::GreetManager {
private:
    std::map<std::string, GreetProvider*> providersByLang ;
	ds4cpp::ComponentFactory *            greetProviderFactory ;
public:
    GreetManagerImpl();
    virtual ~GreetManagerImpl();


    /**
     * Activate callback, called when the component is activated.
     */
    void activate();

	void setComponentFactory(ds4cpp::ComponentFactory* componentFactory) ;
	void unsetComponentFactory(ds4cpp::ComponentFactory* componentFactory) ;

    /*
     * Generated bind method for service greetdemo::GreetProvider
     */
    void addGreetProvider(greetdemo::GreetProvider* greetProvider);

    /*
     * Generated bind method for service greetdemo::GreetProvider
     */
    void removeGreetProvider(greetdemo::GreetProvider* greetProvider);


    std::string getDefaultTarget(const std::string& lang) const ;

    std::string getGreeting(const std::string& lang, const std::string& who) const ;

    std::list<std::string> getAllGreetings(const std::string& who) const ;

    std::list<std::string> getAvailableLanguages() const ;

};

} // namespace greetdemo
#endif /* GREETDEMO_GREETMANAGERIMPL_H_ */

