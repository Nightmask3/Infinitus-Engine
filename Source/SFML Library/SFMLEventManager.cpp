#include "SFMLEventManager.h"


SFMLEventManager::SFMLEventManager(SFMLInputManager &inputHandler)
{
	mInput = &inputHandler;
}


SFMLEventManager::~SFMLEventManager()
{
}

sf::Event & SFMLEventManager::GetEvent()
{
	return mEvent;
}
void SFMLEventManager::SetEventType()									// Used for clarity in the input handler
{
	if (mEvent.type == sf::Event::KeyPressed || mEvent.type == sf::Event::KeyReleased)	// If a key event, sets the type to Keyboard
		mType = Input;
	else if (mEvent.type == sf::Event::MouseButtonPressed || mEvent.type == sf::Event::MouseButtonReleased) // If a mouse event, sets the type to Keyboard
		mType = Input;
	else if (mEvent.type == sf::Event::GainedFocus || mEvent.type == sf::Event::LostFocus) // If a focus event, sets the type to Focus
		mType = Input;
}

SFMLEventType SFMLEventManager::GetEventType()
{
	return mType;
}

void SFMLEventManager::HandleEvent()
{
	//if (mType == Input)					// If an input event, call the input event handler, TODO: Change later when other type of events
		HandleInputEvent();
}

void SFMLEventManager::HandleInputEvent()	// Sends the event manager object to the input manager
{
	mInput->ReceiveEvent(*this);
}