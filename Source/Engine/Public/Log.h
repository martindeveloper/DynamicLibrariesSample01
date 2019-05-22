#pragma once

#include "../Module.h"
#include "../../Bootstrap/Public/Common.h"

class ENGINE_API Log
{
private:
	const char* ModuleName;

public:
	Log(const char* ModuleName);

	void Write(const char* format, ...);
};
