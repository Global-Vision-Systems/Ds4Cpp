/*
 * GenericGreetProviderWrapper.cpp
 * Wrapper for greetdemo.GenericGreetProvider
 */
#include "greetdemo.GenericGreetProvider/include/GenericGreetProvider.hpp"
#include <usBase.h>
#include <ServiceUtils.h>

#include <usServiceProperties.h>

/**
 * @class GenericGreetProviderWrapper
 * The wrapper class for component greetdemo::GenericGreetProvider
 * (provides inheritance with a generic base class for typing purposes)
 */
class GenericGreetProviderWrapper: public ::us::Base, public greetdemo::GenericGreetProvider
{
    public:
    GenericGreetProviderWrapper(const us::ServiceProperties& parameters) : greetdemo::GenericGreetProvider(parameters)
    {
    }    
};

extern "C"
{

DS_ABI_EXPORT GenericGreetProviderWrapper* __greetdemo__GenericGreetProvider__create_param(const us::ServiceProperties& parameters)
{
    return new GenericGreetProviderWrapper(parameters);
}

DS_ABI_EXPORT void __greetdemo__GenericGreetProvider__activate_param(GenericGreetProviderWrapper* object,  const us::ServiceProperties& properties)
{
    object->activate(properties);
}


} // extern "C"

