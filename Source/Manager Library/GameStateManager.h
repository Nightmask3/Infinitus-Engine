#pragma once
#include <SFML/Window/Window.hpp>

class GameStateManager
{
	public:
		void UpdateGameState(sf::Window &w);	// Updates the game state specific to a single window
		GameStateManager();
		virtual ~GameStateManager();
	private:

};

