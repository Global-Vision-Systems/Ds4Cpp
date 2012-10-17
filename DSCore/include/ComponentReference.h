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
 * ComponentReference.h
 *
 *  Created on: 4 mai 2012
 *      Author: simon
 */
#ifndef COMPONENTREFERENCE_H_
#define COMPONENTREFERENCE_H_
#include <string>
using std::string ;
#include <usConfig.h>
namespace ds4cpp
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

{
class ComponentReference
{
public:
    enum Policy
    {
        STATIC, DYNAMIC
    } ;

    enum Cardinality
    {
        SINGLE, MULTIPLE
    } ;

    enum Type
    {
        OPTIONAL_REF, MANDATORY_REF
    } ;

    const string                                name ;
    const string                                target ;
    const string                                interface ;
    const ComponentReference::Policy            policy ;
    const ComponentReference::Cardinality       cardinality ;
    const ComponentReference::Type              type ;
    US_ABI_EXPORT ComponentReference(const string& refName, const string& interface, const string& refTarget = "", ComponentReference::Policy refPolicy =
                                         STATIC, ComponentReference::Cardinality refCardinality =
                                         SINGLE, ComponentReference::Type refType = MANDATORY_REF) ;
    US_ABI_EXPORT ComponentReference(const ComponentReference& cr) ;
    US_ABI_EXPORT virtual ~ComponentReference() ;
    US_ABI_EXPORT ComponentReference& operator=(const ComponentReference& cr) ;
} ;
}       /* namespace ds4cpp */
extern std::ostream& operator<<(std::ostream&, const ds4cpp::ComponentReference&) ;

#endif /* COMPONENTREFERENCE_H_ */
