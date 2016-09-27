# include <chrono>
# include <iostream>
# include "Board.hpp"
# include "display/StdOutDisplay.hpp"
# include "engine/GameLoop.hpp"

using namespace std::chrono;

void                printT(unsigned long int t)
{
	int             m, s, ms, us;

	m = (t / 60000000);
	s = (t / 1000000) % 60;
	ms = (t / 1000) % 1000;
	us = t % 1000;
	printf("Time elapsed: %dm%ds%dms%dus\n", m, s, ms, us);
}

int		main()
{
	GameLoop	game;

	game.loop();
	return (0);
}
