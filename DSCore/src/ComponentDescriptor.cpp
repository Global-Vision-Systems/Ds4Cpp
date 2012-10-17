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
#include "../include/ComponentDescriptor.h"
#include <iostream>
namespace ds4cpp
{
ComponentDescriptor::ComponentDescriptor(const string& componentId, const string& implSharedObject, const vector<string>& providedServices, const vector<ComponentReference>& references, bool immediate, bool autoEnable) : componentId(componentId), implSharedObject(implSharedObject), providedServices(
        new vector<string>(providedServices)), references(
        new vector<ComponentReference>(references)), immediate(
        immediate), autoEnable(autoEnable)
{
}

ComponentDescriptor::ComponentDescriptor(const ComponentDescriptor& component) : componentId(component.componentId), implSharedObject(component.implSharedObject), providedServices(
        component.providedServices), references(component.references), immediate(
        component.immediate), autoEnable(component.autoEnable)
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
    // delete &componentId;
    // delete &implSharedObject;
    delete providedServices ;
    delete references ;
}
}       /* namespace ds4cpp */
std::ostream& operator<<(std::ostream& o, const ds4cpp::ComponentDescriptor& d)
{
    return o << d.componentId ;
}
