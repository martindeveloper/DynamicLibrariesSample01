#pragma once

#ifdef GAME_EXPORTS
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif

#include "../Engine/Public/Log.h"
#include "../Bootstrap/Public/IModule.h"

class GAME_API GameModule : public IModule
{
	typedef Log* (*CreateLogInstanceFunction)(const char*);
	typedef void (*LogWriteMethod)(Log*, const char*, ...);

public:
	virtual void PUBLIC_METHOD_API Initialize() override;

	virtual void OnStart() override;

	virtual void OnDestroy() override;

private:
	Log* Output;
	LogWriteMethod OutputWrite;
};
