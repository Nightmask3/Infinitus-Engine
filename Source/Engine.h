#pragma once
// Windows header files
#include <windows.h>
// C++ header files
#include <iostream>
#include <fstream>
#include <string>
// GLEW and OpenGL header files
#include "..\Dependencies\GLEW\glew.h"	// glew.h needs to be included before GL.h
#include "..\Dependencies\GLEW\wglew.h"
// SFML header files
#include "..\Dependencies\SFML 2.3.2\include\SFML\Window.hpp"
#include "..\Dependencies\SFML 2.3.2\include\SFML\Window\Event.hpp"
#include "..\Dependencies\SFML 2.3.2\include\SFML\Window\VideoMode.hpp"
#include "..\Dependencies\SFML 2.3.2\include\SFML\Graphics.hpp"
//Game Engine Managers header files
#include "..\Source\Manager Library\GameObjectFactory.h"
#include "..\Source\SFML Library\SFMLWindowManager.h"
#include "..\Source\SFML Library\SFMLEventManager.h"
#include "..\Source\SFML Library\SFMLInputManager.h"
#include "..\Source\Manager Library\FrameRateController.h"
#include "..\Source\Physics Library\PhysicsManager.h"
#include "..\Source\Manager Library\ResourceManager.h"
// Graphics module
#include "..\Source\OpenGLRenderer Library\OpenGLRenderer.h"
// Math library header files
#include "..\Source\Math Library\Matrix3D.h"
// Camera Header file
#include "..\Source\Entity Library\Camera.h"
class Engine
{
private:
	// WINDOW MANAGER
	SFMLWindowManager * windowManager;	
	// INPUT HANDLER CREATION
	SFMLInputManager * inputManager;
	// EVENT MANAGER CREATION
	SFMLEventManager * eventManager;
	// FRAME RATE CONTROLLER CREATION
	FrameRateController * frameRateController;	// Creates the frame rate controller
	// GRAPHICS MANAGER
	OpenGLRenderer * graphicsManager;	 // Creates the renderer
	// PHYSICS MANAGER
	PhysicsManager * physicsManager;
	// OBJECT FACTORY CREATION
	GameObjectFactory * objectFactory; // Creates the game object factory
	// RESOURCE MANAGER
	ResourceManager * resourceManager;
	// PLAYER CONTROLLER
	KeyboardControllerComponent * PlayerController;
	// ENEMY MANAGERS (FOR THE TIME BEING, DIRECTLY USING THEIR BEHAVIOR COMPONENTS)
	BehaviorComponent * b1;
	BehaviorComponent * b2;
public:
	Engine();
	virtual ~Engine();
	void Initialize();
	void Load();
	void Update();
	void LoadLevel();
};