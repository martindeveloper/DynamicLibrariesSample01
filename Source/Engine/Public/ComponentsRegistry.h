#pragma once
#include "../../Bootstrap/Public/Common.h"
#include "../../Bootstrap/Public/IModule.h"

#include <vector>
#include <algorithm>

// This class is useless because its using templates which are obviously not avalaible in runtime.
class PUBLIC_API ComponentsRegistry
{
private:
	std::vector<const char*>* RegisteredComponentsName;

public:
	ComponentsRegistry();

	~ComponentsRegistry();
	
	template<typename T>
	bool RegisterComponent();

	template<typename T>
	T* MakeComponent();

private:
	template<typename T>
	bool CanMakeComponent() const;
};
