#pragma once

#ifdef _WINDLL
#define PUBLIC_API __declspec(dllexport)
#define PUBLIC_FUNCTION_API __declspec(dllexport) /*__stdcall*/
#else
#define PUBLIC_API __declspec(dllimport)
#define PUBLIC_FUNCTION_API __declspec(dllimport) /*__stdcall*/
#endif // _WINDLL

#define PUBLIC_METHOD_API __fastcall

// Using extern C for modules entry-points for overcoming C++ name mangling and direct ctor calling
// if you want to use class method as entrypoint instead of plain function.
#define MODULE_BLOCK extern "C"
#define MODULE_ENTRYPOINT_NAME "ModuleEntrypoint"
#define MODULE_ENTRYPOINT PUBLIC_FUNCTION_API IModule* ModuleEntrypoint
#define MODULE_RETURN(InModule) return dynamic_cast<IModule*>(InModule);
#define MODULE_EXTENSION ".dll"

#include <iostream>
