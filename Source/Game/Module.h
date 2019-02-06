#pragma once
#include "../Bootstrap/Public/IModule.h"

class PUBLIC_API GameModule : public IModule
{
public:
	virtual void PUBLIC_METHOD_API Initialize() override;

	virtual void OnStart() override;

	virtual void OnDestroy() override;
};
