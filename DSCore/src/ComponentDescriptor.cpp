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
 * ComponentDescriptor.cpp
 *
 *  Created on: 4 mai 2012
 *      Author: simon
 */
#include "ComponentDescriptor.h"
#include <iostream>

US_USE_NAMESPACE
namespace ds4cpp
{
ComponentDescriptor::ComponentDescriptor(const string& componentId, const string& implSharedObject, const vector<string>& providedServices, const vector<ComponentReference>& references, const us::ServiceProperties& properties, bool immediate, bool autoEnable, bool singleton) : 
		componentId(componentId),
		implSharedObject(implSharedObject), 
		providedServices(new vector<string>(providedServices)),
		references(new vector<ComponentReference>(references)), 
		properties(new ServiceProperties(properties)),
		immediate(immediate), 
		autoEnable(autoEnable),
		singleton(singleton)
{
}

ComponentDescriptor::ComponentDescriptor(const ComponentDescriptor& component) : 
		componentId(component.componentId), 
		implSharedObject(component.implSharedObject), 
		providedServices(component.providedServices),
		references(component.references), 
		properties(component.properties),
		immediate(component.immediate), 
		autoEnable(component.autoEnable),
		singleton(component.singleton)
{
}

// const string& ComponentDescriptor::getComponentId() const {
// return componentId;
// }
//
// const string& ComponentDescriptor::getImplSharedObject() const {
// return implSharedObject;
// }
//
// const vector<string>& ComponentDescriptor::getProvidedServices() const {
// return providedServices;
// }
//
// const bool ComponentDescriptor::getAutoEnable() const {
// return autoEnable;
// }
//
// const bool ComponentDescriptor::getImmediate() const {
// return immediate;
// }
//
// const vector<ComponentReference>& ComponentDescriptor::getReferences() const {
// return references;
// }
ComponentDescriptor::~ComponentDescriptor()
{
    delete providedServices ;
    delete references ;
    delete properties ;
}
}       /* namespace ds4cpp */
std::ostream& operator<<(std::ostream& o, const ds4cpp::ComponentDescriptor& d)
{
    return o << d.componentId ;
}
