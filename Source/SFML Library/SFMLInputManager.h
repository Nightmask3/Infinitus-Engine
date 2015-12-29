#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
// C++ HEADERFILES
#include <iostream>
#include <vector>

// SFML HEADERFILES
#include <SFML\Window\Keyboard.hpp>
// MATH LIBRARY HEADER FILE
#include "..\Math Library\Vector3D.h"
// MANAGER HEADER FILES
#include "SFMLEventManager.h"
#include "SFMLWindowManager.h"
// COMPONENT HEADER FILES
#include "..\Component Library\Component.h"
#include "..\..\Dependencies\GLEW\glew.h"

enum InputEventType
{
	Keyboard,	// Keyboard events
	Mouse,		// Mouse events
	JoyStick,	// Joystick events
	Focus		// Window Focus events
};
//////// Forward Declarations ////////
class SFMLEventManager; 
class SFMLWindowManager;
//////// Forward Declarations ////////
class SFMLInputManager
{
	public:
		SFMLInputManager(SFMLWindowManager &windowManager);
		~SFMLInputManager();
		// MOUSE HANDLING STUFF
		bool isMouseButtonPressed(sf::Mouse::Button);
		Vector3D GetMousePosition();
		// INPUT DEVICE UPDATION STUFF
		void UpdateInputState();
		// EVENT HANDLING STUFF
		void ReceiveEvent(SFMLEventManager &);	// Gets the reference to event manager type (for getting the event), passes it to appropriate function for input handling
		// KEY STATE CHECKING STUFF - ABSTRACTION ON TOP OF SFML 
		bool isKeyPressed(sf::Keyboard::Key);					
		bool isKeyReleased(sf::Keyboard::Key);
		bool isKeyTriggered(sf::Keyboard::Key);
		// ARRAY OF CONTROLLER COMPONENTS
		std::vector<Component *> ControllerList;

	private:
		bool keyboardStatePrev[sf::Keyboard::KeyCount] ;	// Holds the state of all the keyboard keys in the previous frame
		bool keyboardStateCurr[sf::Keyboard::KeyCount];		// Holds the state of all the keyboard keys in the current frame
		SFMLWindowManager * owningWinMan;					// Holds the window manager to have the ability to close window through input
	
};

#endif