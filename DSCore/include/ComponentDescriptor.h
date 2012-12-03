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
 * ComponentDescriptor.h
 *
 *  Created on: 4 mai 2012
 *      Author: simon
 */
#ifndef COMPONENTDESCRIPTOR_H_
#define COMPONENTDESCRIPTOR_H_
#pragma warning( disable: 4251 )
#pragma warning( disable: 4099 )
#include <map>
#include <string>
#include <vector>
#include <ostream>
#include "ComponentReference.h"
#include "usServiceProperties.h"
using std::string ;
using std::vector ;
using std::map ;
namespace ds4cpp
{
class US_ABI_EXPORT ComponentDescriptor
{
public:
// Properties
    const string                componentId ;      /**< Component identifier */
    const string                implSharedObject ; /**< Name of the handling module */
    const vector<string>*       providedServices ; /**< List of the provided services */
    vector<ComponentReference>* references ;       /**< List of the reference services */
	us::ServiceProperties*      properties ;       /**< Base component properties with unresolved variables */
    const bool                  immediate ;        /**< */
    const bool                  autoEnable ;       /**< */
	bool						singleton ;        /**< Is it a singleton or a factory ? */

//Methods
	ComponentDescriptor(const string& componentId, const string& implSharedObject, const vector<string>& providedServices, const vector<ComponentReference>& references, const us::ServiceProperties& properties, bool immediate = false, bool autoEnable = true, bool singleton = true) ;
    ComponentDescriptor(const ComponentDescriptor& component) ;
    virtual ~ComponentDescriptor() ;

    // const string& getComponentId() const;
    // const string& getImplSharedObject() const;
    // const vector<string>& getProvidedServices() const;
    // const vector<ComponentReference>& getReferences() const;
    // const bool getAutoEnable() const;
    // const bool getImmediate() const;
} ;
}       /* namespace ds4cpp */
extern std::ostream& operator<<(std::ostream&, const ds4cpp::ComponentDescriptor&) ;

#endif /* COMPONENTDESCRIPTOR_H_ */
