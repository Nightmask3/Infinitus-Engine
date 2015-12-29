#pragma once

// File Name : GameObjectFactory.h
// Responsible for the creation of game objects and to populate the game object with components
// C++ HEADERFILES 
#include <sstream>
#include <vector>
#include <typeinfo>
#include <typeindex>
// GAME OBJECT
#include "..\Entity Library\GameObject.h"
// MANAGERS
#include "..\OpenGLRenderer Library\OpenGLRenderer.h"
#include "..\SFML Library\SFMLInputManager.h"
#include "..\Physics Library\PhysicsManager.h"
#include "..\Manager Library\FrameRateController.h"
// COMPONENTS
#include "..\Component Library\TransformComponent.h"
#include "..\Component Library\SpriteComponent.h"
#include "..\Component Library\KeyboardControllerComponent.h"
#include "..\Component Library\PhysicsComponent.h"
#include "..\Component Library\BehaviorComponent.h"

class PhysicsManager;
class GameObjectFactory
{
	private:
		SFMLInputManager & InputManager;
		OpenGLRenderer & GraphicsManager;
		PhysicsManager & PhyManager;
		FrameRateController & FrameManager;
	public:
		// TODO : Maybe switch access modifier for Object library and add getters and setters
		std::vector<GameObject> ObjectLibrary;
		GameObjectFactory(
			SFMLInputManager &in, 
			OpenGLRenderer &gl, 
			PhysicsManager &phy, 
			FrameRateController & frame
			) : InputManager(in), GraphicsManager(gl), PhyManager(phy), FrameManager(frame)
		{ ObjectLibrary.reserve(2048); }
		void CreateGameObject();
		void LoadObject(const char *pFileName);
		virtual ~GameObjectFactory(){};					// TODO : Garbage collection of all game objects
		template <typename T> bool CreateComponent()	// Member Template function used to create component of any type
		{
			Component * mComponent = nullptr;
			// Create component type as requested
			if (typeid(T) == typeid(TransformComponent))
			{
				mComponent = new TransformComponent();
				mComponent->mOwner = &(ObjectLibrary.back());		// Gets last created Game Object 
				mComponent->mOwner->ComponentListSize++;			// Increments component list size of Game Object
				mComponent->mOwner->ComponentList.push_back(mComponent);// Adds the newly created component to game object component list
				return true;
			}
			else if (typeid(T) == typeid(SpriteComponent))
			{
				mComponent = new SpriteComponent();
				mComponent->mOwner = &(ObjectLibrary.back());
				mComponent->mOwner->ComponentListSize++;		
				mComponent->mOwner->ComponentList.push_back(mComponent);
				GraphicsManager.SpriteList.push_back(mComponent);
				return true;
			}
			else if (typeid(T) == typeid(KeyboardControllerComponent))
			{
				mComponent = new KeyboardControllerComponent(InputManager, FrameManager);
				mComponent->mOwner = &(ObjectLibrary.back());
				mComponent->mOwner->ComponentListSize++;
				mComponent->mOwner->ComponentList.push_back(mComponent);
				InputManager.ControllerList.push_back(mComponent);
				return true;
			}
			else if (typeid(T) == typeid(PhysicsComponent))
			{
				mComponent = new PhysicsComponent();
				mComponent->mOwner = &(ObjectLibrary.back());
				mComponent->mOwner->ComponentListSize++;
				mComponent->mOwner->ComponentList.push_back(mComponent);
				// Sets current position to use in physics simulation
				TransformComponent * t = nullptr;
				t = static_cast<TransformComponent *>(mComponent->mOwner->GetComponent(Component::TRANSFORM));
				
				PhysicsComponent * p = nullptr;
				p = static_cast<PhysicsComponent *>(mComponent->mOwner->GetComponent(Component::PHYSICS));

				Vector3DSet(&(p->mPositionCurr), t->mTranslation.m[0][3], t->mTranslation.m[1][3], t->mTranslation.m[2][3], 1);
				PhyManager.PhysicsObjectsList.push_back(mComponent);
				return true;
			}
			else if (typeid(T) == typeid(BehaviorComponent))
			{
				mComponent = new BehaviorComponent();
				mComponent->mOwner = &(ObjectLibrary.back());
				mComponent->mOwner->ComponentListSize++;
				mComponent->mOwner->ComponentList.push_back(mComponent);
				return true;
			}
			/* TODO : Add more component types here */
			else
			{
				std::cout << "Component Type not currently implemented OR Invalid Component Type." << std::endl;
			}
			return false;
		}

};

