#include "../Public/ComponentsRegistry.h"

ComponentsRegistry::ComponentsRegistry()
{
	this->RegisteredComponentsName = new std::vector<const char*>();
};

ComponentsRegistry::~ComponentsRegistry()
{
	delete this->RegisteredComponentsName;
};

template<typename T>
bool ComponentsRegistry::RegisterComponent()
{
	const char* name = typeid(T).name();

	bool isComponentAlreadyRegistered = this->CanMakeComponent<T>();

	if (isComponentAlreadyRegistered)
	{
		std::cerr << "Component " << name << " is already registered" << std::endl;

		return false;
	}

	this->RegisteredComponentsName->push_back(name);

	return true;
};

template<typename T>
bool ComponentsRegistry::CanMakeComponent() const
{
	const char* name = typeid(T).name();

	return (std::find(this->RegisteredComponentsName->begin(), this->RegisteredComponentsName->end(), name) != this->RegisteredComponentsName->end());
};

template<typename T>
T* ComponentsRegistry::MakeComponent()
{
	if (!CanMakeComponent)
	{
		std::cerr << "Component " << name << " is not registered, therefore it can not be made" << std::endl;

		return std::nullptr;
	}

	T* componentInstance = new T();

	return componentInstance;
};
