#pragma once
#include "Common.h"

class IModule
{
public:
	virtual void Initialize() = 0;

	virtual void OnStart() = 0;

	virtual void OnDestroy() = 0;
};
