# include <chrono>
# include <iostream>
# include "Board.hpp"
# include "display/StdOutDisplay.hpp"
# include "engine/GameLoop.hpp"
# include "utilities/Parser.hpp"

void	disp(Parser::PlayerType p)
{
	switch (p) {
		case Parser::PlayerType::AI:
			std::cout << "AI";
			break;
		case Parser::PlayerType::HUMAN:
			std::cout << "HUMAN";
			break;
		case Parser::PlayerType::NONE:
			std::cout << "NONE";
			break;
	};
}

int		main(int argc, char **argv)
{
	Parser::PlayerType	p1;
	Parser::PlayerType	p2;

	p1 = Parser::getPlayer(argc, argv, 1);
	p2 = Parser::getPlayer(argc, argv, 1);
	std::cout << "p1: ";
	disp(p1);
	std::cout << std::endl << "p2:";
	disp(p2);
	std::cout << std::endl;
	GameLoop	game(p1, p2);
	game.launchGame();
	return (0);
}
