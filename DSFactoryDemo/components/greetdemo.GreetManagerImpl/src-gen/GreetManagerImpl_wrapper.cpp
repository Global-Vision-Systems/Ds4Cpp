/*
 * GreetManagerImplWrapper.cpp
 * Wrapper for greetdemo.GreetManagerImpl
 */
#include "greetdemo.GreetManagerImpl/include/GreetManagerImpl.hpp"
#include <usBase.h>
#include <ServiceUtils.h>


/**
 * @class GreetManagerImplWrapper
 * The wrapper class for component greetdemo::GreetManagerImpl
 * (provides inheritance with a generic base class for typing purposes)
 */
class GreetManagerImplWrapper: public ::us::Base, public greetdemo::GreetManagerImpl
{
};

extern "C"
{

DS_ABI_EXPORT GreetManagerImplWrapper* __greetdemo__GreetManagerImpl__create()
{
    return new GreetManagerImplWrapper;
}

DS_ABI_EXPORT void __greetdemo__GreetManagerImpl__activate(GreetManagerImplWrapper* object)
{
	object->activate();
}

DS_ABI_EXPORT void __greetdemo__GreetManagerImpl__add_greetdemo__GreetProvider(GreetManagerImplWrapper* object, ::us::Base *service)
{
	greetdemo::GreetProvider* lservice = dynamic_cast<greetdemo::GreetProvider*>(service);
	object->addGreetProvider(lservice);
}

DS_ABI_EXPORT void __greetdemo__GreetManagerImpl__remove_greetdemo__GreetProvider(GreetManagerImplWrapper* object, ::us::Base *service)
{
	greetdemo::GreetProvider* lservice = dynamic_cast<greetdemo::GreetProvider*>(service);
	object->removeGreetProvider(lservice);
}
DS_ABI_EXPORT void __greetdemo__GreetManagerImpl__set_ds4cpp__ComponentFactory(GreetManagerImplWrapper* object, ::us::Base *service)
{
	ds4cpp::ComponentFactory* lservice = dynamic_cast<ds4cpp::ComponentFactory*>(service);
	object->setComponentFactory(lservice);
}

DS_ABI_EXPORT void __greetdemo__GreetManagerImpl__unset_ds4cpp__ComponentFactory(GreetManagerImplWrapper* object, ::us::Base *service)
{
	ds4cpp::ComponentFactory* lservice = dynamic_cast<ds4cpp::ComponentFactory*>(service);
	object->unsetComponentFactory(lservice);
}

} // extern "C"

