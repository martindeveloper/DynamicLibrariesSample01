#include "../Public/Log.h"

Log::Log(const char* ModuleName)
{
	this->ModuleName = ModuleName;
}

void Log::Write(const char* format, ...)
{
	std::cout << "[" << this->ModuleName << "] " << format << std::endl;
};
