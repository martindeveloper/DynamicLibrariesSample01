#include "../../../Bootstrap/Public/Common.h"

class PUBLIC_API IComponent
{
public:
	virtual void OnStart() = 0;

	// OnTick
	// OnDestroy
	// OnWhatever
};