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
#include <vector>
#include <list>
#include <map>

#include "ComponentDescriptor.h"
#include "ComponentDescriptor.h"

#include <usBase.h>
#include <usServiceProperties.h>
#include <usServiceReference.h>

namespace ds4cpp
{
class Component ;
class ComponentInstance
{
	friend class ComponentManagerImpl ;
	friend class Component ;

private:
    bool                                                satisfied ;
    std::multimap<std::string, us::ServiceReference>    serviceReferences ;
	::us::Base *                                        instanceObject ;
	::us::ServiceProperties                             properties ;
	Component *                                         component ;
	std::vector<ComponentReference>                     resolvedReferences ;

    void bindService(const std::string& interface, us::ServiceReference serviceObject) ;
    void unbindService(const std::string& interface, us::ServiceReference serviceObject) ;

    bool enableInstance() ;

    void injectAllReferences() ;
    void injectReference(const std::string & interface, us::ServiceReference) ;

    void computeSatisfied() ;

	std::string replaceVariableInTarget(std::string target) ;

public:
	ComponentInstance(Component *component, const us::ServiceProperties& overrideProperties) ;
    virtual ~ComponentInstance() ;

	Component*                             getComponent() const ;
	const ::us::ServiceProperties&         getProperties() const ;
	const std::vector<ComponentReference>& getResolvedReferences() const ;

	void set(::us::Base *instance) ;

	bool isValid() const ;
	bool isSatisfied() const ;
} ;
}       /* namespace ds4cpp */
#endif /* COMPONENTINSTANCE_H_ */
