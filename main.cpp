# include <chrono>
# include <iostream>
# include <cstdlib>
# include <ctime>
# include "Board.hpp"
# include "display/StdOutDisplay.hpp"
# include "engine/GameLoop.hpp"
# include "utilities/Parser.hpp"

int		main(int argc, char **argv)
{
	Parser::PlayerType	p1;
	Parser::PlayerType	p2;

	std::srand(std::time(0));
	p1 = Parser::getPlayer(argc, argv, 1);
	p2 = Parser::getPlayer(argc, argv, 2);
	GameLoop	game(p1, p2);
	game.launchGame();
	return (0);
}
