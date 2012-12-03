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

/**
 * Service interface greetdemo::GreetManager
 * Generated on Fri Jun 15 14:30:10 CEST 2012
 */
#ifndef GREETDEMO_GREETMANAGER_H_
#define GREETDEMO_GREETMANAGER_H_

#include <string>
#include <list>

namespace greetdemo {

/*interface*/ struct GreetManager
{
    // Destructor must be virtual
    virtual ~GreetManager()
    {
    }
    
    virtual std::string getDefaultTarget(const std::string& lang) const = 0 ;

    virtual std::string getGreeting(const std::string& lang, const std::string& who) const = 0 ;

    virtual std::list<std::string> getAllGreetings(const std::string& who) const = 0 ;

    virtual std::list<std::string> getAvailableLanguages() const = 0 ;

	virtual void reset() = 0 ;
} ;

} // namespace greetdemo

#endif /* GREETDEMO_GREETMANAGER_H_ */
