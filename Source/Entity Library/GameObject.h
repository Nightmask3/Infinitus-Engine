#pragma once
#include <vector>
#include "..\Source\Component Library\Component.h"
// Forward Declaration
class Component;
class GameObject
{
	public:
		std::vector<Component *> ComponentList;		// Using a vector of pointers because components can be of different sizes from base class Component
	public:											// Also to take advantage of the polymorphic function invocation
		Component * GetComponent(Component::ComponentType);					
		unsigned int ComponentListSize;				// Holds the size of the component list
		GameObject();
		~GameObject();
};



