# include <chrono>
# include <iostream>
# include "Board.hpp"
# include "display/StdOutDisplay.hpp"
# include "engine/GameLoop.hpp"

int		main()
{
	GameLoop	game;

	game.launchGame();
	return (0);
}
