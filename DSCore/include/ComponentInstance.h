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

#include <usBase.h>
#include <usServiceProperties.h>
#include <usServiceReference.h>
#include <usServiceRegistration.h>

namespace ds4cpp
{
class Component ;
class ComponentInstance
{
	friend class ComponentManagerImpl ;
	friend class Component ;

private:
    bool                                                satisfied ;                    /**< Is the component satisfied ? */
    std::multimap<std::string, us::ServiceReference>    serviceReferences ;            /**< Association between service reference name and us::ServiceReference */
	std::map<std::string, us::ServiceRegistration>      providedServiceRegistration ;  /**< Reference of the provided services */  
	::us::Base *                                        instanceObject ;               /**< Created with wrapper object ptr (can be null) */
	::us::ServiceProperties                             properties ;                   /**< Service properties affected by ldap filter (given to activate method) */
	::us::ServiceProperties                             componentParameters ;          /**< Component parameter given to the object constructor */
	Component *                                         component ;                    /**< Component ptr */
	std::vector<ComponentReference>                     resolvedReferences ;           /**< Reference list with variable replaced by their value */

	/**
	 * Bind a service
	 */
    void bindService(const std::string& interface, const std::string& refName, us::ServiceReference serviceObject) ;
	/**
	 * Unbind a service
	 */
    void unbindService(const std::string& interface, const std::string& refName, us::ServiceReference serviceObject) ;

    bool enableInstance() ;

	// Inject
    void injectAllReferences() ;
    void injectReference(const std::string & interface, const std::string& refName, us::ServiceReference) ;

	// Uninject
    void uninjectReference(const std::string & interface, const std::string& refName, us::ServiceReference) ;

	/**
	 * Compute if this instance if satisfied
	 */
    void computeSatisfied() ;

	/**
	 * Replace a filter variable with this value (variable = $(.*))
	 */
	std::string replaceVariableInTarget(std::string target) ;

public:
	ComponentInstance(Component *component, const us::ServiceProperties& overrideProperties, const us::ServiceProperties& componentParameters = us::ServiceProperties()) ;
    virtual ~ComponentInstance() ;

	Component*                             getComponent() const ;
	const ::us::ServiceProperties&         getProperties() const ;
	const ::us::ServiceProperties&         getComponentParameters() const ;
	const std::vector<ComponentReference>& getResolvedReferences() const ;
	US_ABI_EXPORT us::Base*                getInstance() const ;

	void set(::us::Base *instance) ;
	void unregister() ;

	bool isValid() const ;
	bool isSatisfied() const ;
} ;
}       /* namespace ds4cpp */
#endif /* COMPONENTINSTANCE_H_ */
