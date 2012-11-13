//   Copyright 2012 - Global Vision Systems
//   Based on library CppMicroServices, Copyright (c) German Cancer Research Center,
//                                    Division of Medical and Biological Informatics
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
 * Launcher.cpp
 *  Created on: 7 mai 2012
 *      Author: simon
 */
#pragma warning( disable: 4251 )
#include <vector>
#include <algorithm>
#include <iostream>

#include <usModuleActivator.h>
#include <usModuleContext.h>
#include "ModuleLoader.cpp"
US_USE_NAMESPACE

 /**
 * This class implements a module activator that uses the module
 * context to register an English language dictionary service
 * with the C++ Micro Services registry during static initialization
 * of the module. The dictionary service interface is
 * defined in a separate file and is implemented by a nested class.
 */
 class US_ABI_LOCAL MyActivator: public ModuleActivator {

 public:

 /**
 * Implements ModuleActivator::Load(). Registers an
 * instance of a dictionary service using the module context;
 * attaches properties to the service that can be queried
 * when performing a service look-up.
 * @param context the context for the module.
 */
 void Load(ModuleContext* context) {
 std::cout << "Hello World" << std::endl;
 context->AddServiceListener(this, &MyActivator::handleEvent);
 }

 /**
 * Implements ModuleActivator::Unload(). Does nothing since
 * the C++ Micro Services library will automatically unregister any registered services.
 * @param context the context for the module.
 */
 void Unload(ModuleContext* /*context*/) {
 // NOTE: The service is automatically unregistered
 }

 void handleEvent(const ServiceEvent event) {
 std::cout
 << event.GetServiceReference().GetProperty(
 ServiceConstants::OBJECTCLASS()) << " "
 << event.GetType() << std::endl;
 }

 };

 US_EXPORT_MODULE_ACTIVATOR(LauncherModule, MyActivator)
 //![Activator]
#include <usModuleInitialization.h>
US_INITIALIZE_MODULE("LauncherModule", "", "", "1.0.0")
using namespace std ;
ModuleLoader* loadModule(const char* moduleName, int* cptLoadedModules)
{
    try
    {
        ModuleLoader* module = new ModuleLoader(moduleName) ;
        module->Load() ;
        (*cptLoadedModules)++ ;
        return module ;
    }
    catch (std::runtime_error& error)
    {
		US_ERROR << error.what() ;
    }

    return NULL ;
}

#define SEPARATOR        "###############################################"
void printSeparator()
{
    cout << SEPARATOR << endl ;
}

std::string selectDemo()
{
	bool valid = false ;
	while (!valid)
	{
		cout << "which demo do you want to use ? (default DSDemo) " << std::endl << "1. DSDemo" << std::endl << "2. DSFactoryDemo" << std::endl ;
		std::string choice ;
		cin >> choice ;
		if (choice.empty())
		{
			return "DSDemo" ;
		}
		if (std::isdigit(choice.c_str()[0]))
		{
			int num = atoi(choice.c_str()) ;
			if (num == 1)
				return "DSDemo" ;
			else if (num == 2)
				return "DSFactoryDemo" ;
		}
	}
}

int main(int /*argc*/, char* /*argv*/ [])
{
    {
        printSeparator() ;
        cout << "######         Generic Launcher         #######" << endl ;
        printSeparator() ;
        cout << "Loading modules" << endl ;
        int             cptLoadedModules = 0 ;

        // Loading modules
        // loadModule("SimpleModule", &cptLoadedModules);
		std::string debugFlag = "";
#ifdef _DEBUG
		debugFlag = "d" ;
#endif
		std::string demoModule = selectDemo() ;

		loadModule(std::string(std::string("DSCore") + debugFlag).c_str(), &cptLoadedModules) ;
		loadModule(std::string(std::string("DSBridge") + debugFlag).c_str(), &cptLoadedModules) ;
		loadModule(std::string(demoModule + debugFlag).c_str(), &cptLoadedModules) ;
        vector<Module*> modules ;
        ModuleRegistry::GetLoadedModules(modules) ;
        cout << cptLoadedModules << " modules have been loaded" << endl ;
        printSeparator() ;
        cout << "Available modules:" << endl ;
        for (auto it = modules.begin() ; it != modules.end() ; ++it)
        {
            cout << "* " << (*it)->GetName() << endl ;
        }
        printSeparator() ;
        cout << "Available services:" << endl ;
        auto refs = GetModuleContext()->GetServiceReferences("") ;
        for (auto it = refs.begin() ; it != refs.end() ; ++it)
        {
            cout << "* " << (*it).GetProperty(ServiceConstants::OBJECTCLASS())
            << endl ;
        }
        printSeparator() ;
    }
    return 0 ;
}
