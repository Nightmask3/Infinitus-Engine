#pragma once
// File Name : GameObjectFactory.h
// Responsible for the creation of game objects.
// Uses the Component Factory class to populate the game object with components
#include <vector>
#include <typeinfo>
#include <typeindex>

#include "..\Source\Entity Library\GameObject.h"
#include "..\Source\Component Library\TransformComponent.h"
#include "..\Source\Component Library\SpriteComponent.h"
class GameObjectFactory
{
	public:	 // TODO : Maybe switch access modifier for Object library and add getters and setters
		std::vector<GameObject> ObjectLibrary;
		
	public:
		void CreateGameObject();
		// Reference to the component factory being used by this game object factory
		// Initializes Component Factory reference, sets the Component Factory owner to be this Game Object Factory
		GameObjectFactory() {};
		virtual ~GameObjectFactory(){};
		template <typename T> bool CreateComponent()	// Member Template function used to create component of any type
		{
			Component * mComponent = nullptr;
			// Create component type as requested
			if (typeid(T) == typeid(TransformComponent))
			{
				mComponent = new TransformComponent();
				mComponent->mOwner = &(ObjectLibrary.back());		// Gets last created Game Object 
				mComponent->mOwner->ComponentList.push_back(mComponent);
				return true;
			}
			if (typeid(T) == typeid(SpriteComponent))
			{
				mComponent = new SpriteComponent();
				mComponent->mOwner = &(ObjectLibrary.back());		// Gets last created Game Object 
				mComponent->mOwner->ComponentList.push_back(mComponent);
				return true;
			}
			return false;
			/* TODO : Add more component types here */
		}

};

