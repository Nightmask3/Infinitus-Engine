#pragma once
#include <vector>
#include "..\Component Library\Component.h"
#include "..\Manager Library\EventManager.h"
class GameObject
{
public:
	std::vector<Component *> ComponentList;		// Using a vector of pointers because components can be of different sizes from base class Component
												// Also to take advantage of the polymorphic function invocation
	unsigned int ComponentListSize;				// Holds the size of the component list
public:
	GameObject() : ComponentListSize(0) {}
	virtual ~GameObject() {}
	Component * GetComponent(Component::ComponentType);
	void HandleEvent(Event *);
};



