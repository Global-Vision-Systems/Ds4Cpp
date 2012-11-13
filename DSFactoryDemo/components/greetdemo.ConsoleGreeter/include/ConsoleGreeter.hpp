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
 * ConsoleGreeter.hpp
 * Component greetdemo.ConsoleGreeter
 * Created on: Fri Jun 15 14:16:26 CEST 2012
 */

#ifndef GREETDEMO_CONSOLEGREETER_H_
#define GREETDEMO_CONSOLEGREETER_H_

#include <greetdemo/GreetManager.hpp>

namespace greetdemo {

class ConsoleGreeter {
private:
	GreetManager* greetManager;
public:
    ConsoleGreeter();
    virtual ~ConsoleGreeter();


    /**
     * Activate callback, called when the component is activated.
     */
    void activate();

    /*
     * Generated bind method for service greetdemo::GreetManager
     */
    void setGreetManager(greetdemo::GreetManager* greetManager);

    /*
     * Generated bind method for service greetdemo::GreetManager
     */
    void unsetGreetManager(greetdemo::GreetManager* greetManager);



};

} // namespace greetdemo
#endif /* GREETDEMO_CONSOLEGREETER_H_ */

