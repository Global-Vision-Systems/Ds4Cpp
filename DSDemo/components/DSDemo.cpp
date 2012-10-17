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

#include <usModuleActivator.h>
#include <usModuleContext.h>
#include <usServiceProperties.h>
#include <ModuleUtils.h>

#include <usBase.h>

#include <memory>
#include <vector>


US_USE_NAMESPACE
using namespace ds4cpp;

class DSDemoComponentProvider: public ds4cpp::ComponentProvider, public us::Base {
private:
    Module* module;
public:
    DSDemoComponentProvider(Module* module) :
            module(module) {
    }

    std::vector<ds4cpp::ComponentDescriptor*>* getComponentDescriptors() const {
        std::vector<ds4cpp::ComponentDescriptor*>* result = new std::vector<
                ds4cpp::ComponentDescriptor*>;


        // greetdemo.EnglishGreetProvider
        {
            std::vector<ComponentReference>* references = new std::vector<
                    ComponentReference>;
                                
            std::vector<std::string> services;
            services.push_back("greetdemo::GreetProvider");

            ComponentDescriptor* componentDesc =
                    new ds4cpp::ComponentDescriptor(
                            "greetdemo::EnglishGreetProvider",
                            "" /* containing module */, services, *references, true,
                            true);

            result->push_back(componentDesc);
        }
        // greetdemo.FrenchGreetProvider
        {
            std::vector<ComponentReference>* references = new std::vector<
                    ComponentReference>;
                                
            std::vector<std::string> services;
            services.push_back("greetdemo::GreetProvider");

            ComponentDescriptor* componentDesc =
                    new ds4cpp::ComponentDescriptor(
                            "greetdemo::FrenchGreetProvider",
                            "" /* containing module */, services, *references, true,
                            true);

            result->push_back(componentDesc);
        }
        // greetdemo.GreetManagerImpl
        {
            std::vector<ComponentReference>* references = new std::vector<
                    ComponentReference>;
            references->push_back(
                    ComponentReference("greetdemo::GreetProvider", "greetdemo::GreetProvider",
                            std::string(), ComponentReference::DYNAMIC,
                            ComponentReference::MULTIPLE,
                            ComponentReference::OPTIONAL_REF));
                                
            std::vector<std::string> services;
            services.push_back("greetdemo::GreetManager");

            ComponentDescriptor* componentDesc =
                    new ds4cpp::ComponentDescriptor(
                            "greetdemo::GreetManagerImpl",
                            "" /* containing module */, services, *references, true,
                            true);

            result->push_back(componentDesc);
        }
        // greetdemo.ConsoleGreeter
        {
            std::vector<ComponentReference>* references = new std::vector<
                    ComponentReference>;
            references->push_back(
                    ComponentReference("greetdemo::GreetManager", "greetdemo::GreetManager",
                            std::string(), ComponentReference::STATIC,
                            ComponentReference::SINGLE,
                            ComponentReference::MANDATORY_REF));
                                
            std::vector<std::string> services;

            ComponentDescriptor* componentDesc =
                    new ds4cpp::ComponentDescriptor(
                            "greetdemo::ConsoleGreeter",
                            "" /* containing module */, services, *references, true,
                            true);

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
                new DSDemoComponentProvider(context->GetModule()));

    }

    void Unload(ModuleContext* /*context*/)
    {
    }

};

#ifdef _DEBUG
US_EXPORT_MODULE_ACTIVATOR(DSDemod, Activator)
#else
US_EXPORT_MODULE_ACTIVATOR(DSDemo, Activator)
#endif
//![Activator]

#include <usModuleInitialization.h>


#ifdef _DEBUG
US_INITIALIZE_MODULE("DS Greet Demo", "DSDemod", "", "1.0.0")
#else
US_INITIALIZE_MODULE("DS Greet Demo", "DSDemo", "", "1.0.0")
#endif

