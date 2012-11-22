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

/**
 * Module definition for DSDemo
 */
#include <ComponentProvider.h>
#include <ds4cpp/ComponentFactory.hpp>

#include <usModuleActivator.h>
#include <usModuleContext.h>
#include <usServiceProperties.h>
#include <ModuleUtils.h>

#include <usBase.h>

#include <memory>
#include <vector>


US_USE_NAMESPACE
using namespace ds4cpp;

class DSFactoryDemoComponentProvider: public ds4cpp::ComponentProvider, public us::Base {
private:
    Module* module;
public:
    DSFactoryDemoComponentProvider(Module* module) :
            module(module) {
    }

    std::vector<ds4cpp::ComponentDescriptor*>* getComponentDescriptors() const {
        std::vector<ds4cpp::ComponentDescriptor*>* result = new std::vector<
                ds4cpp::ComponentDescriptor*>;


        // greetdemo.GenericGreetProvider Factory
        {
            std::vector<ComponentReference> references;
                                
            std::vector<std::string> services;
            services.push_back("greetdemo::GreetProvider");

			::us::ServiceProperties                 properties ;
			//Default parameters that will be overrided
			properties[std::string("providedLang")] = std::string("??") ;
			properties[std::string("greeting")] = std::string("??") ;
			properties[std::string("defaultTarget")] = std::string("??") ;

            ComponentDescriptor* componentDesc =
                    new ds4cpp::ComponentDescriptor(
                            "greetdemo::GenericGreetProvider",
                            "" /* containing module */, services, references, properties,
							true, true, false); // False because it is a factory

            result->push_back(componentDesc);
        }
        // greetdemo.GreetManagerImpl
        {
            std::vector<ComponentReference> references ;
            references.push_back(
                    ComponentReference("greetdemo::GreetProvider", "greetdemo::GreetProvider",
							std::string("(providedLang=${requireLang})"), ComponentReference::DYNAMIC, //Dynamic LDAP Filter (useful for factory)
                            ComponentReference::MULTIPLE,
                            ComponentReference::OPTIONAL_REF));
			// Require GenericGreetProvider factory
			std::string factoryTarget = "(" + DS4CPP_FACTORY_COMPONENT_NAME + "=greetdemo::GenericGreetProvider)" ;
            references.push_back(
				ComponentReference(DS4CPP_FACTORY_SERVICE_NAME, DS4CPP_FACTORY_SERVICE_NAME,
				factoryTarget, ComponentReference::DYNAMIC, 
                            ComponentReference::SINGLE,
							ComponentReference::MANDATORY_REF));
                                
            std::vector<std::string> services;
            services.push_back("greetdemo::GreetManager");

			::us::ServiceProperties                 properties ;
			properties[std::string("requireLang")] = std::string("*") ; //Target will be replaced by this

			ComponentDescriptor* componentDesc =
                    new ds4cpp::ComponentDescriptor(
                            "greetdemo::GreetManagerImpl",
                            "" /* containing module */, services, references, properties,
							true, true);

            result->push_back(componentDesc);
        }
        // greetdemo.ConsoleGreeter
        {
            std::vector<ComponentReference> references;
            references.push_back(
                    ComponentReference("greetdemo::GreetManager", "greetdemo::GreetManager",
                            std::string(), ComponentReference::STATIC,
                            ComponentReference::SINGLE,
                            ComponentReference::MANDATORY_REF));
                                
            std::vector<std::string> services;
			::us::ServiceProperties                 properties ;

            ComponentDescriptor* componentDesc =
                    new ds4cpp::ComponentDescriptor(
                            "greetdemo::ConsoleGreeter",
                            "" /* containing module */, services, references, properties,
							true, true);

            result->push_back(componentDesc);
        }

        return result;
    }

    Module* getProvider() const
    {
        return module;
    }
};

class US_ABI_LOCAL Activator: public ModuleActivator
{
public:

    void Load(ModuleContext* context) {
        context->RegisterService("ds4cpp::ComponentProvider",
                new DSFactoryDemoComponentProvider(context->GetModule()));

    }

    void Unload(ModuleContext* /*context*/)
    {
    }

};

#ifdef _DEBUG
US_EXPORT_MODULE_ACTIVATOR(DSFactoryDemod, Activator)
#else
US_EXPORT_MODULE_ACTIVATOR(DSFactoryDemo, Activator)
#endif
//![Activator]

#include <usModuleInitialization.h>


#ifdef _DEBUG
US_INITIALIZE_MODULE("DS Greet Factory Demo", "DSFactoryDemod", "", "1.0.0")
#else
US_INITIALIZE_MODULE("DS Greet Factory Demo", "DSFactoryDemo", "", "1.0.0")
#endif

