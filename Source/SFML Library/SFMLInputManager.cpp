#include "SFMLInputManager.h"

SFMLInputManager::SFMLInputManager(SFMLWindowManager &windowManager)
{
	for (int i = 0; i < sf::Keyboard::KeyCount + 1; i++) // Initializes the value of keyboard state map to 0 when input manager is created
	{
		keyboardStatePrev[i] = false;
		keyboardStateCurr[i] = false;
	}
	owningWinMan = &windowManager;								
}
SFMLInputManager::~SFMLInputManager()
{

}
void SFMLInputManager::ReceiveEvent(SFMLEventManager &EventMan)		// Performs the checking for some basic functionality like exit, focus, window resizing etc.
{
	// In case of different types events handle accordingly
	if (EventMan.GetEvent().type == sf::Event::GainedFocus) // try to get rid of type field here, use get event type instead
		std::cout << "Gained Focus" << std::endl;
	else if (EventMan.GetEvent().type == sf::Event::LostFocus)
		std::cout << "Lost Focus" << std::endl;
	else if ((EventMan.GetEvent().type == sf::Event::Closed) || ((EventMan.GetEvent().type == sf::Event::KeyPressed) && (EventMan.GetEvent().key.code == sf::Keyboard::Escape)))
		owningWinMan->GetWin().close();
	else if (EventMan.GetEvent().type == sf::Event::Resized)
		glViewport(0, 0, EventMan.GetEvent().size.width, EventMan.GetEvent().size.height);
}

void SFMLInputManager::UpdateInputState()			// Updates the state of input devices
{
	
	sf::Keyboard::Key key;							// Used to check the input state of each keyboard key
	for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
	{
		key = static_cast<sf::Keyboard::Key>(i);		
		if (sf::Keyboard::isKeyPressed(key) && keyboardStateCurr[key] == false)
		{
			keyboardStateCurr[key] = true;
		}
		else if (sf::Keyboard::isKeyPressed(key) && keyboardStateCurr[key] == true)
		{
			keyboardStateCurr[key] = true;
			keyboardStatePrev[key] = true;
		}
		else if (!sf::Keyboard::isKeyPressed(key) && keyboardStateCurr[key] == true)
		{
			keyboardStateCurr[key] = false;
			keyboardStatePrev[key] = true;
		}
		else if (!sf::Keyboard::isKeyPressed(key) && keyboardStatePrev[key] == true)
		{
			keyboardStateCurr[key] = false;
			keyboardStatePrev[key] = false;
		}
	}
}
bool SFMLInputManager::isKeyPressed(sf::Keyboard::Key key)
{
	return keyboardStateCurr[key] && keyboardStatePrev[key];		// When a key is pressed in both this frame and previous frame returns true
}

bool SFMLInputManager::isKeyTriggered(sf::Keyboard::Key key)
{
	return  keyboardStateCurr[key] && !keyboardStatePrev[key];		// True in current frame but not in previous frame
}

bool SFMLInputManager::isKeyReleased(sf::Keyboard::Key key)
{
	return  !keyboardStateCurr[key] && keyboardStatePrev[key]; 		// When key is not pressed in this frame but pressed in previous frame return true
}

bool SFMLInputManager::isMouseButtonPressed(sf::Mouse::Button mbutton)	// Returns true or false based on whether this mouse button is pressed currently
{
	return sf::Mouse::isButtonPressed(mbutton);
}
Vector3D SFMLInputManager::GetMousePosition()						// Returns mouse position relative to window
{
	sf::Vector2i temp = sf::Mouse::getPosition(owningWinMan->GetWin());
	Vector3D temp1(temp.x, temp.y, 0, 1);
	std::cout << "Mouse Position X :" << temp1.x << "\tMouse Position Y :" << temp1.y << "\r";;
	return temp1;
}