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
 *
 *  Created on: 10 mai 2012
 *      Author: simon
 */
#include "ComponentDescriptorBridge.cpp"
#include <usBase.h>
using namespace ds4cpp ;
class ComponentDescriptorBridgeWrapper : public::us::Base,
    public ComponentDescriptorBridge
{
} ;

extern "C" {
US_ABI_EXPORT ComponentDescriptorBridgeWrapper* __ds4cpp__ComponentDescriptorBridge__create()
{
    return new ComponentDescriptorBridgeWrapper ;
}

// void __ds4cpp_ComponentDescriptorBridge__destroy(
// ComponentDescriptorBridge* object) {
// delete object;
// }
US_ABI_EXPORT void __ds4cpp__ComponentDescriptorBridge__set_ds4cpp__ComponentManager(ComponentDescriptorBridgeWrapper* object, ::us::Base* service)
{
    ds4cpp::ComponentManager* lservice =
        dynamic_cast<ds4cpp::ComponentManager*>(service) ;
    object->setComponentManager(lservice) ;
}

US_ABI_EXPORT void __ds4cpp__ComponentDescriptorBridge__add_ds4cpp__ComponentProvider(ComponentDescriptorBridgeWrapper* object, ::us::Base* service)
{
    ds4cpp::ComponentProvider* lservice =
        dynamic_cast<ds4cpp::ComponentProvider*>(service) ;
    object->addComponentProvider(lservice) ;
}

US_ABI_EXPORT void __ds4cpp__ComponentDescriptorBridge__remove_ds4cpp__ComponentProvider(ComponentDescriptorBridgeWrapper* object, ::us::Base* service)
{
    ds4cpp::ComponentProvider* lservice =
        dynamic_cast<ds4cpp::ComponentProvider*>(service) ;
    object->removeComponentProvider(lservice) ;
}
}
