#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

// WOULD BECOME PART OF THE RENDERER DLL LATER ON (?)
#include <SFML\Window.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Window\VideoMode.hpp>
#include <SFML\Graphics.hpp>

class SFMLWindowManager
{
private:
	sf::VideoMode mVideoMode;			// Used as the default video mode when user does not specify
	sf::Window mWindow;					// Holds the window object
public:
	SFMLWindowManager();			    // Constructor
	virtual ~SFMLWindowManager();		// Destructor, virtual because who knows when we'll need to inherit from window manager
	void CreateWin(sf::Window &mWin);   // Used to create the window
	sf::Window & GetWin();				// Getter for the window object
	sf::VideoMode & GetVideoMode();		// Getter for the video mode object
};

#endif // !WINDOWMANAGER_H