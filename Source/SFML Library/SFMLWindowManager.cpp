#include "SFMLWindowManager.h"

SFMLWindowManager::SFMLWindowManager()
{
	mVideoMode = mVideoMode.getDesktopMode();		// Gets the users desktop video mode to use in window creation
}

SFMLWindowManager:: ~SFMLWindowManager()
{
	mWindow.~Window();
}

sf::Window & SFMLWindowManager::GetWin()				// Getter for the window object
{
	return mWindow;
}
sf::VideoMode & SFMLWindowManager::GetVideoMode()		// Getter for the window object
{
	return mVideoMode;
}

void SFMLWindowManager::CreateWin(sf::Window &mWin)		// Creates the window itself
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	// Replace with desktop mode later
	mWin.create(sf::VideoMode(800, 600), "Infinitus Engine", sf::Style::Default, settings);
}
