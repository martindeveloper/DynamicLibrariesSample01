#include "Module.h"
#include "../Bootstrap/Public/IModule.h"

void ComponentsModule::Initialize()
{
	std::cout << "Components module is initialized" << std::endl;
};

void ComponentsModule::OnStart()
{
	std::cout << "ComponentsModule::OnStart called" << std::endl;
};

void ComponentsModule::OnDestroy()
{
	std::cout << "ComponentsModule::OnDestroy called" << std::endl;
};

MODULE_BLOCK
{
	MODULE_ENTRYPOINT()
	{
		ComponentsModule* components = new ComponentsModule();
		components->Initialize();

		MODULE_RETURN(components);
	};
}
