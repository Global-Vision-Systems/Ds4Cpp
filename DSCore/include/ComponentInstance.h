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
 * ComponentInstance.h
 *
 *  Created on: 4 mai 2012
 *      Author: simon
 */
#ifndef COMPONENTINSTANCE_H_
#define COMPONENTINSTANCE_H_
#include "ComponentDescriptor.h"
#include <usBase.h>
namespace ds4cpp
{
class ComponentInstance
{
    friend class Component ;

private:
    ::us::Base * instanceObject ;

public:
    ComponentInstance(::us::Base* instance) ;
    virtual ~ComponentInstance() ;
} ;
}       /* namespace ds4cpp */
#endif /* COMPONENTINSTANCE_H_ */
