// Fix some linking issues, not good way, just hax, dont care now. fyi this should be fix in premake config
// Or use WindowApp instead console and use CRT entrypoint instead main
#pragma comment(linker, "/INCLUDE:mainCRTStartup")

// Strip some unnecessary stuff
// Include windows headers only in modules which actually needs it, do not put it into Common
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

#include "../Public/Common.h"
#include "../Public/IModule.h"

#include "../../Engine/Module.h"

typedef IModule*(*ModuleEntrypointFunction)();

void OnExit(int code);

int main()
{
	constexpr int modulesCount = 3;
	const char* libraries[modulesCount] = {"Engine", "Components", "Game"};

	thread_local EngineModule* engineModule = nullptr;

	for(int i = 0; i < modulesCount; i++)
	{
		const char* library = libraries[i];
		char moduleLibraryFileName[256];

		strncpy_s(moduleLibraryFileName, library, sizeof(moduleLibraryFileName));
		strncat_s(moduleLibraryFileName, MODULE_EXTENSION, sizeof(moduleLibraryFileName));

		HINSTANCE moduleHandle = LoadLibrary(moduleLibraryFileName);

		if (!moduleHandle)
		{
			std::cout << "Could not load the module library: " << moduleLibraryFileName << std::endl;

			OnExit(EXIT_FAILURE);
		}

		std::cout << "Module library loaded: " << moduleLibraryFileName << std::endl;

		ModuleEntrypointFunction getModuleObject = (ModuleEntrypointFunction)GetProcAddress(moduleHandle, MODULE_ENTRYPOINT_NAME);

		if (!getModuleObject)
		{
			std::cout << "Could not locate module " << library << " entrypoint " << MODULE_ENTRYPOINT_NAME << std::endl;

			OnExit(EXIT_FAILURE);
		}

		std::cout << "Module" << library << " entrypoint " << MODULE_ENTRYPOINT_NAME << " was found" << std::endl;

		IModule* loadedModule = getModuleObject();
		loadedModule->OnStart();

		// Engine may need a special threatment
		if (library == "Engine")
		{
			engineModule = static_cast<EngineModule*>(loadedModule);
		}

		std::cout << std::endl;
	}

	if (engineModule != nullptr)
	{
		engineModule->StartMainThread();
		engineModule->WaitForMainThreadDecay();
	}

	return EXIT_SUCCESS;
}

void OnExit(int code)
{
	std::cin.get();

	std::exit(code);
}
