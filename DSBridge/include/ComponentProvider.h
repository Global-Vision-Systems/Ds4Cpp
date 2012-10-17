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
 * ComponentProvider.h
 *
 *  Created on: 10 mai 2012
 *      Author: simon
 */
#ifndef COMPONENTPROVIDER_H_
#define COMPONENTPROVIDER_H_
#include <vector>
#include "ComponentDescriptor.h"
#include "ServiceUtils.h"
#include <usModule.h>
US_USE_NAMESPACE
namespace ds4cpp
{
struct ComponentProvider
{
    virtual ~ComponentProvider()
    {
    }

    virtual std::vector<ComponentDescriptor*>* getComponentDescriptors() const = 0 ;

    virtual Module* getProvider() const = 0 ;
} ;
}
DECLARE_SERVICE_INTERFACE(ds4cpp::ComponentProvider) ;
#endif /* COMPONENTPROVIDER_H_ */
