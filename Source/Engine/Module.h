#pragma once
#include "Public/ComponentsRegistry.h"
#include "../Bootstrap/Public/IModule.h"

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

#include <mutex>
#include <thread>
#include <chrono>

class PUBLIC_API EngineModule : public IModule
{
private:
	ComponentsRegistry* Registry;

	bool IsEngineMainLoopRunning : 1;

	std::mutex* LockIsEngineMainLoopRunning;

	unsigned __int64 TimeBase;

	unsigned __int64 TimeDelta;

	unsigned __int64 TimeFrequency;

	std::thread* MainThread;

public:
	virtual void PUBLIC_METHOD_API Initialize() override;

	virtual void OnStart() override;

	virtual void OnDestroy() override;

	virtual void StartMainThread();

	virtual void RequestMainThreadDecay();

	virtual void WaitForMainThreadDecay();

private:
	void ChangeMainThreadState(bool InState);

	void Tick(double DeltaTime);

	void MainThreadRunner();
};
