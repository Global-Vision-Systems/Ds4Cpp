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

#include <ComponentManager.h>
#include <usModuleActivator.h>
#include <usModuleContext.h>
#include <usServiceProperties.h>

#include <usBase.h>
#include <algorithm>
#include <memory>
US_USE_NAMESPACE
using namespace ds4cpp ;
class US_ABI_LOCAL Activator : public ModuleActivator
{
private:
    void logFail()
    {
		US_ERROR << "Fatal error: could not retrieve ComponentManager service" ;
    }

public:
    void Load(ModuleContext* context)
    {
        // Retrieve ComponentManager
        ServiceReference                        ref = context->GetServiceReference<ComponentManager>() ;
        if (!ref)
        {
            logFail() ;
            return ;
        }
        ComponentManager*                       componentManager = context->GetService<
            ComponentManager>(ref) ;
        if (!componentManager)
        {
            logFail() ;
            return ;
        }

        // We have the ComponentManager, manually create the ComponentDescriptor for the
        // Bridge Component
        std::vector<ComponentReference>*        references      = new std::vector<ComponentReference>() ;
        std::string                             managerName     = "ds4cpp::ComponentManager" ;  // std::string(us_service_interface_iid<ComponentManager*>());
        references->push_back(ComponentReference(managerName, managerName, std::string(),
                                                 ComponentReference::STATIC, ComponentReference::SINGLE,
                                                 ComponentReference::MANDATORY_REF)) ;
        std::string                             providerName = "ds4cpp::ComponentProvider" ;    // std::string(us_service_interface_iid<ComponentManager*>());
        references->push_back(ComponentReference(providerName, providerName, std::string(),
                                                 ComponentReference::DYNAMIC, ComponentReference::MULTIPLE,
                                                 ComponentReference::OPTIONAL_REF)) ;
        std::vector<std::string>                services ;                                      // no provided services
        ComponentDescriptor*                    bridgeDesc = new ComponentDescriptor("ds4cpp::ComponentDescriptorBridge",
                                                                                     "", services, *references, true,
                                                                                     true) ;

        // Provide the descriptor to the ComponentManager so that the party can begin!
        componentManager->newComponent(context->GetModule(), *bridgeDesc) ;
    }

    void Unload(ModuleContext* /*context*/)
    {
    }
} ;

#include <usModuleInitialization.h>
#ifdef _DEBUG
US_EXPORT_MODULE_ACTIVATOR(DSBridged, Activator)
US_INITIALIZE_MODULE("Component Descriptor Provider Bridge", "DSBridged", "", "1.0.0")
#else
US_EXPORT_MODULE_ACTIVATOR(DSBridge, Activator)
US_INITIALIZE_MODULE("Component Descriptor Provider Bridge", "DSBridge", "", "1.0.0")
#endif
