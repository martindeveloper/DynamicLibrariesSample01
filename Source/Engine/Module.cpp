#include "Module.h"
#include "Public/Log.h"

void EngineModule::Initialize()
{
	std::cout << "Engine module is initialized" << std::endl;
};

void EngineModule::OnStart()
{
	std::cout << "EngineModule::OnStart called" << std::endl;

	LockIsEngineMainLoopRunning = new std::mutex();

	QueryPerformanceFrequency((LARGE_INTEGER*)&TimeFrequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&TimeBase);
};

void EngineModule::OnDestroy()
{
	std::cout << "EngineModule::OnDestroy called" << std::endl;

	delete LockIsEngineMainLoopRunning;

	if (MainThread != nullptr)
	{
		delete MainThread;
	}
}

void EngineModule::Tick(double DeltaTime)
{
	using namespace std::chrono_literals;

	std::cout << "EngineModule::Tick is ticking with DeltaTime = " << DeltaTime << std::endl;

	std::this_thread::sleep_for(5s);
}

void EngineModule::ChangeMainThreadState(bool InState)
{
	LockIsEngineMainLoopRunning->lock();

	IsEngineMainLoopRunning = InState;

	LockIsEngineMainLoopRunning->unlock();
}

void EngineModule::MainThreadRunner()
{
	ChangeMainThreadState(true);

	double deltaTimePrevious = 0;

	do
	{
		unsigned __int64 time;
		QueryPerformanceCounter((LARGE_INTEGER*)&time);

		double deltaTime = (double)(time - TimeBase)*(1.0 / (double)TimeFrequency);

		this->Tick((deltaTime - deltaTimePrevious));

		deltaTimePrevious = deltaTime;
	} while (IsEngineMainLoopRunning);
}

void EngineModule::StartMainThread()
{
	MainThread = new std::thread(&EngineModule::MainThreadRunner, this);
}

void EngineModule::WaitForMainThreadDecay()
{
	MainThread->join();
}

void EngineModule::RequestMainThreadDecay()
{
	ChangeMainThreadState(false);
}

MODULE_BLOCK
{
	MODULE_ENTRYPOINT()
	{
		EngineModule* engine = new EngineModule();
		engine->Initialize();

		MODULE_RETURN(engine);
	};

	PUBLIC_FUNCTION_API Log* CreateLogInstanceWithName(const char* name)
	{
		return new Log(name);
	}
}
