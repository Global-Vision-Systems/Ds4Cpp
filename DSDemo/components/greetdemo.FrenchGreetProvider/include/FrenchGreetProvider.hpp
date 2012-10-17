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
 * FrenchGreetProvider.hpp
 * Component greetdemo.FrenchGreetProvider
 * Created on: Fri Jun 15 14:34:26 CEST 2012
 */

#ifndef GREETDEMO_FRENCHGREETPROVIDER_H_
#define GREETDEMO_FRENCHGREETPROVIDER_H_

#include <greetdemo/GreetProvider.hpp>

namespace greetdemo {

class FrenchGreetProvider: public greetdemo::GreetProvider {
private:

public:
    FrenchGreetProvider();
    virtual ~FrenchGreetProvider();


    /**
     * Activate callback, called when the component is activated.
     */
    void activate();


    std::string getDefaultTarget() const ;

    std::string getGreeting(const std::string& who) const ;

    std::string getLang() const ;

};

} // namespace greetdemo
#endif /* GREETDEMO_FRENCHGREETPROVIDER_H_ */

