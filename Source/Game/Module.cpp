#include "Module.h"
#include "../Bootstrap/Public/IModule.h"

void GameModule::Initialize()
{
	std::cout << "Game module is initialized" << std::endl;
};

void GameModule::OnStart()
{
	std::cout << "GameModule::OnStart called" << std::endl;
};

void GameModule::OnDestroy()
{
	std::cout << "GameModule::OnDestroy called" << std::endl;
};

MODULE_INITIALIZE(GameModule);
