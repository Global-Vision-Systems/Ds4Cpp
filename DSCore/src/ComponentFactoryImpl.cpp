#include "ComponentFactoryImpl.h"
#include "Component.h"
#include "ComponentManagerImpl.h"

namespace ds4cpp
{
ComponentFactoryImpl::ComponentFactoryImpl(ComponentManagerImpl *componentManager, Component *buildComponent) : buildComponent(buildComponent), componentManager(componentManager)
{
	// Build factory descriptor
	us::ServiceProperties properties ;
	properties[DS4CPP_FACTORY_COMPONENT_NAME] = buildComponent->descriptor.componentId ;
	properties[DS4CPP_FACTORY_PROVIDED_SERVICE_NAME] = *buildComponent->descriptor.providedServices ;

	std::vector<std::string> providedServices ;
	providedServices.push_back(DS4CPP_FACTORY_SERVICE_NAME) ;

	// For the moment Factory hasn't got any reference
	std::vector<ComponentReference> references ;

	factoryDescriptor = new ComponentDescriptor(buildComponent->descriptor.componentId + std::string(".factory"), std::string(), 
												providedServices, references, properties, true, true, true) ;
}

ComponentFactoryImpl::~ComponentFactoryImpl()
{
	delete factoryDescriptor ;
}

ComponentDescriptor *ComponentFactoryImpl::getFactoryDescriptor() const
{
	return factoryDescriptor ;
}

ComponentInstance *ComponentFactoryImpl::create(const ::us::ServiceProperties& serviceProperties, const ::us::ServiceProperties& componentParameters)
{
	ComponentInstance* instance = componentManager->newComponentInstance(buildComponent, serviceProperties, componentParameters) ;
	builtInstancies.push_back(instance) ;
	return instance ;
}

const us::ServiceProperties& ComponentFactoryImpl::getFactoryProperties() const
{
	return *factoryDescriptor->properties ;
}

bool ComponentFactoryImpl::_remove(us::Base* service)
{
	if (service)
	{
		for (auto it = builtInstancies.begin(); it != builtInstancies.end(); ++it)
		{
			if ((*it)->getInstance() != NULL && (*it)->getInstance() == service)
			{
				// Found !
				componentManager->outcomingComponentInstance(*it) ;
				return true ;
			}
		}
	}
	US_ERROR << "In component factory [" << this->factoryDescriptor->componentId << " unable to remove provided service" ;
	// Not found
	return false ;
}
}