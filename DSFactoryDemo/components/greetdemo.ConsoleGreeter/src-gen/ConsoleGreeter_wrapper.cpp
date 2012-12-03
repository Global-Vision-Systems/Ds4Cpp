/*
 * ConsoleGreeterWrapper.cpp
 * Wrapper for greetdemo.ConsoleGreeter
 */
#include "greetdemo.ConsoleGreeter/include/ConsoleGreeter.hpp"
#include <usBase.h>
#include <ServiceUtils.h>


/**
 * @class ConsoleGreeterWrapper
 * The wrapper class for component greetdemo::ConsoleGreeter
 * (provides inheritance with a generic base class for typing purposes)
 */
class ConsoleGreeterWrapper: public ::us::Base, public greetdemo::ConsoleGreeter
{
};

extern "C"
{

DS_ABI_EXPORT ConsoleGreeterWrapper* __greetdemo__ConsoleGreeter__create()
{
    return new ConsoleGreeterWrapper;
}

DS_ABI_EXPORT void __greetdemo__ConsoleGreeter__activate(ConsoleGreeterWrapper* object)
{
	object->activate();
}

DS_ABI_EXPORT void __greetdemo__ConsoleGreeter__set_greetdemo__GreetManager(ConsoleGreeterWrapper* object, ::us::Base *service)
{
	greetdemo::GreetManager* lservice = dynamic_cast<greetdemo::GreetManager*>(service);
	object->setGreetManager(lservice);
}

DS_ABI_EXPORT void __greetdemo__ConsoleGreeter__unset_greetdemo__GreetManager(ConsoleGreeterWrapper* object, ::us::Base *service)
{
	greetdemo::GreetManager* lservice = dynamic_cast<greetdemo::GreetManager*>(service);
	object->unsetGreetManager(lservice);
}

} // extern "C"

