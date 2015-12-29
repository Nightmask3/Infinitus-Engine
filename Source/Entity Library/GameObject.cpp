#include "GameObject.h"


Component * GameObject::GetComponent(Component::ComponentType type)
{
	for (std::vector<Component *>::iterator i = ComponentList.begin(); i != ComponentList.end(); i++)
	{
		if ((*i)->mType == type)
		{
			return (*i);
		}
	}
	/*std::cout << "No component of that type exists in this Game Object\n";*/
	return nullptr;
}

void GameObject::HandleEvent(Event * pEvent)
{
	for (auto i : ComponentList)
	{
		i->HandleEvent(pEvent);
	}
}