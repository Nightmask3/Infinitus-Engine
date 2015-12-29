#pragma once
#include <SFML\System\Clock.hpp> // sf::Clock, sf::Time
#include <SFML\Window.hpp>		 // sf::GetFrameTime()

#include "..\SFML Library\SFMLWindowManager.h"
// Forward Declaration
class SFMLWindowManager;

class FrameRateController
{
public:
	// Total time accumulator
	double t;
	// Frame time limit
	double dt;
	// Actual time since last frame
	double frametime;
	sf::Clock mClock;
	sf::Time frameTime;
	sf::Time currentTime;
	sf::Time newTime;
	SFMLWindowManager & WindowManager;
public:
	FrameRateController(SFMLWindowManager &wm) : WindowManager(wm){ frameTime = sf::Time(); currentTime = sf::Time(); newTime = sf::Time();  dt = 0.0f; t = 0.0f; }
	~FrameRateController();
	void updateFrameTime();
	sf::Time getFrameTime() { return frameTime; }
	void EnableFrameRateLimit(unsigned int Limit);
	void ToggleVSync(bool value);
};