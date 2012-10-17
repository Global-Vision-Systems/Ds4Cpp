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
 * ComponentReference.cpp
 *
 *  Created on: 4 mai 2012
 *      Author: simon
 */
#include "../include/ComponentReference.h"
#include <iostream>
namespace ds4cpp
{
ComponentReference::ComponentReference(const string& refName, const string& interface, const string& refTarget, ComponentReference::Policy refPolicy, ComponentReference::Cardinality refCardinality, ComponentReference::Type refType) : name(refName), interface(interface), target(refTarget), policy(
        refPolicy), cardinality(refCardinality), type(refType)
{
}

ComponentReference::ComponentReference(const ComponentReference& cr) : name(cr.name), interface(cr.interface), target(cr.target), policy(
        cr.policy), cardinality(cr.cardinality), type(cr.type)
{
}

ComponentReference& ComponentReference::operator=(const ComponentReference& cr)
{
    return *this ;
}

ComponentReference::~ComponentReference()
{
}
}

/* namespace ds4cpp */
std::ostream& operator<<(std::ostream& o, const ds4cpp::ComponentReference& ref)
{
    return o << ref.name ;
}
