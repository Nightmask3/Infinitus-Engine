#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "SFMLEventManager.h"
#include "SFMLWindowManager.h"
#include <xstddef>

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

		// INPUT DEVICE UPDATION STUFF
		void UpdateInputState();
		// EVENT HANDLING STUFF
		void ReceiveEvent(SFMLEventManager &);	// Gets the reference to event manager type (for getting the event), passes it to appropriate function for input handling
		// KEY STATE CHECKING STUFF - ABSTRACTION ON TOP OF SFML 
		bool isKeyPressed(sf::Keyboard::Key);					
		bool isKeyReleased(sf::Keyboard::Key);
		bool isKeyTriggered(sf::Keyboard::Key);
		
	private:
		//std::unordered_map<int, bool> keyboardStatePrev;	// Holds the state of all the keyboard keys in the previous frame
		//std::unordered_map<int, bool> keyboardStateCurr;	// Holds the state of all the keyboard keys in the current frame
		bool keyboardStatePrev[sf::Keyboard::KeyCount] ;	// Holds the state of all the keyboard keys in the previous frame
		bool keyboardStateCurr[sf::Keyboard::KeyCount];		// Holds the state of all the keyboard keys in the current frame
		sf::Keyboard::Key mKey;								// Holds the keyboard key that triggered the event being handled
		sf::Mouse::Button mButton;							// Holds the mouse button that triggered the event being handled
		SFMLWindowManager * owningWinMan;					// Holds the window manager to have the ability to close window through input
};

#endif