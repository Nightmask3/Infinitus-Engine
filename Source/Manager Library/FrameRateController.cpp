#include "FrameRateController.h"

void FrameRateController::EnableFrameRateLimit(unsigned int Limit)
{
	// Sets frame time limit
	dt = 1.0f / Limit;
	// Starts the clock
	mClock = sf::Clock();
	currentTime = mClock.getElapsedTime();
}
void FrameRateController::updateFrameTime()
{
	newTime = mClock.getElapsedTime();
	frameTime = newTime - currentTime;
	frametime = frameTime.asSeconds();
	currentTime = newTime;
}
void FrameRateController::ToggleVSync(bool value)
{
	WindowManager.GetWin().setVerticalSyncEnabled(value);
}