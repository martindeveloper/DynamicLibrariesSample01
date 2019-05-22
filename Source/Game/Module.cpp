#include "Module.h"

#include "../Bootstrap/Public/IModule.h"

void GameModule::Initialize()
{
	HINSTANCE engineModuleHandle = LoadLibrary("Engine.dll");

	if (engineModuleHandle != nullptr)
	{
		CreateLogInstanceFunction createLogInstanceFunction = (CreateLogInstanceFunction)GetProcAddress(engineModuleHandle, "CreateLogInstanceWithName");

		// Runtime linking by manually getting address of Log::Write alternatively this can be by marking method as `virtual` which routes method calls to vtable
		// Or you can switch to Load-Time Linking by adding `Links { "Engine" }` to premake which will use `Engine.lib` while building `Game.dll`
		// This will create dependency in `Game.dll` for `Engine.dll` and OS will load `Engine.dll` while `Game.dll` is initialized 
		// And you can call methods like `Output->Write(...)`
		OutputWrite = (LogWriteMethod)GetProcAddress(engineModuleHandle, "?Write@Log@@QEAAXPEBDZZ"); // The mangled name is very fragile

		Output = createLogInstanceFunction("Game");

		// First argument is passed as `this`
		OutputWrite(Output, "Game module is initialized");
	}

	OutputWrite(Output, "Game module is initialized");
};

void GameModule::OnStart()
{
	OutputWrite(Output, "GameModule::OnStart called");
};

void GameModule::OnDestroy()
{
	OutputWrite(Output, "GameModule::OnDestroy called");
};

MODULE_INITIALIZE(GameModule);
