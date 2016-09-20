# include <chrono>
# include <iostream>
# include <unistd.h>
# include "Board.hpp"

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
	Board b;
	bool	res;
	
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	res = b.isWinningBoard();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
	if (res)
		std::cout << "Won" << std::endl;
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
	printT(duration);
	return (0);
}
