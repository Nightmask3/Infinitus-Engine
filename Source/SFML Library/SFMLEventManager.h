#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

#include "SFMLInputManager.h"
enum SFMLEventType
{
	Input,		// Events generated through interaction with an input device
	NonInput	// All other types of events
};

class SFMLInputManager; // Forward Declaration

class SFMLEventManager
{
	public:
		SFMLEventManager(SFMLInputManager &inputHandler);
		virtual ~SFMLEventManager();
		sf::Event & GetEvent();		// Gets the event associated with the instance of the event manager
		void SetEventType();		// Sets mType based on the type of the SFML event
		SFMLEventType GetEventType();	// Getter to retrieve the Event Type
		void HandleEvent();			// Handles the event based on its mType
		void HandleInputEvent();	// The tradeoff function where the event is passed to input manager for handling
		
	private:
		sf::Event mEvent;			// The event returned by polling the window
		SFMLEventType mType;			// Assigns an event type from the enum EventType based on the type of mEvent
		SFMLInputManager * mInput;	// Used to call functions in the input manager
};
#endif
