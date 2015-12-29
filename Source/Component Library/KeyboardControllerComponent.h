// File Name : Keyboard Controller Component.
// Description : Responsible for handling all the keyboard related input events that are of interest to the parent Gameobject
#pragma once
#define MOVE_SPEED 8.0f
#include "..\Entity Library\GameObject.h"
#include "..\SFML Library\SFMLInputManager.h"
#include "..\Manager Library\FrameRateController.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
class KeyboardControllerComponent : public Component
{
	public:
		bool mGameWon;
		void Update();
		void Serialize(std::string &, unsigned int &);
		SFMLInputManager & InputManager; // Gets a reference to the input manager upon creation
		FrameRateController & FrameController;
		KeyboardControllerComponent(SFMLInputManager & input, FrameRateController & frame) : InputManager(input), FrameController(frame), Component(Component::KBCONTROLLER) { mGameWon = false; }
		virtual ~KeyboardControllerComponent(){}
};