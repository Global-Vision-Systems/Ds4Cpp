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

	std::vector<std::string> providedServices ;
	providedServices.push_back(DS4CPP_FACTORY_SERVICE_NAME) ;

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

ComponentInstance *ComponentFactoryImpl::create(const ::us::ServiceProperties& properties)
{
	return componentManager->newComponentInstance(buildComponent, properties) ;
}
}