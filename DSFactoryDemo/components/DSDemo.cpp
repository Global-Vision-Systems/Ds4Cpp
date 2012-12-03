/**
 * Module definition for DSDemo
 */
#include <ComponentProvider.h>

#include <usModuleActivator.h>
#include <usModuleContext.h>
#include <usServiceProperties.h>
#include <ModuleUtils.h>

// Replace that include with your own base class declaration
#include <usBase.h>

#include <memory>
#include <vector>


US_USE_NAMESPACE
using namespace ds4cpp;

/**
 * @class DSDemoComponentProvider
 * Provides the components in the module DSDemo
 */
class DSDemoComponentProvider: public ds4cpp::ComponentProvider, public us::Base {
private:
    Module* module; /**< The module instance */
public:
    /**
     * Constructor for DSDemoComponentProvider
     * @param[in] module The provider module instance
     */
    DSDemoComponentProvider(Module* module) :
            module(module) {
    }

    /**
     * Service method that returns the components provided by the module.
     * @return the descriptors of components provided
     */
    std::vector<ds4cpp::ComponentDescriptor*>* getComponentDescriptors() const {
        std::vector<ds4cpp::ComponentDescriptor*>* result = new std::vector<
                ds4cpp::ComponentDescriptor*>;


        // greetdemo.GenericGreetProvider
        {
            std::vector<ComponentReference> references;
                                
            std::vector<std::string> services;
            services.push_back("greetdemo::GreetProvider");
            
            ::us::ServiceProperties properties;

            ComponentDescriptor* componentDesc =
                    new ds4cpp::ComponentDescriptor(
                            "greetdemo::GenericGreetProvider",
                            "" /* containing module */, services, references, properties, true,
                            true, false);

            result->push_back(componentDesc);
        }
        // greetdemo.GreetManagerImpl
        {
            std::vector<ComponentReference> references;
            references.push_back(
                    ComponentReference("greetdemo::GreetProvider", "greetdemo::GreetProvider",
                            std::string(""), ComponentReference::DYNAMIC,
                            ComponentReference::MULTIPLE,
                            ComponentReference::OPTIONAL_REF));
            references.push_back(
                    ComponentReference("ds4cpp::ComponentFactory", "ds4cpp::ComponentFactory",
                            std::string("(component.name=greetdemo::GreetProvider)"), ComponentReference::DYNAMIC,
                            ComponentReference::SINGLE,
                            ComponentReference::MANDATORY_REF));
                                
            std::vector<std::string> services;
            services.push_back("greetdemo::GreetManager");
            
            ::us::ServiceProperties properties;

            ComponentDescriptor* componentDesc =
                    new ds4cpp::ComponentDescriptor(
                            "greetdemo::GreetManagerImpl",
                            "" /* containing module */, services, references, properties, true,
                            true, true);

            result->push_back(componentDesc);
        }
        // greetdemo.ConsoleGreeter
        {
            std::vector<ComponentReference> references;
            references.push_back(
                    ComponentReference("greetdemo::GreetManager", "greetdemo::GreetManager",
                            std::string(""), ComponentReference::STATIC,
                            ComponentReference::SINGLE,
                            ComponentReference::MANDATORY_REF));
                                
            std::vector<std::string> services;
            
            ::us::ServiceProperties properties;

            ComponentDescriptor* componentDesc =
                    new ds4cpp::ComponentDescriptor(
                            "greetdemo::ConsoleGreeter",
                            "" /* containing module */, services, references, properties, true,
                            true, true);

            result->push_back(componentDesc);
        }

        return result;
    }

    /**
     * Returns the module instance
     * @return the module instance
     */
    Module* getProvider() const
    {
        return module;
    }
};

/**
 * @class Activator
 * The activator of module DSDemo
 */
class US_ABI_LOCAL Activator: public ModuleActivator
{
public:
    /**
     * Callback called when the module is loaded.
     * @param[in] context the module context
     */
    void Load(ModuleContext* context) {
        context->RegisterService("ds4cpp::ComponentProvider",
                new DSDemoComponentProvider(context->GetModule()));

    }

    /**
     * Callback called when the module is unloaded.
     * @param[in] context the module context
     */
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

