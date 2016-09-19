#include "players/STDINPlayer.hpp"

int		main()
{
	STDINPlayer		p;
	AbstractPlayer	*p2;
	int				move;

	p2 = &p;
	move = p2->getMove();
	std::cout << "move: " << move << std::endl;
	return (0);
}
