#include "Grid.hpp"
#include <iostream>

int	main()
{
	Grid	grid;

	std::cout << grid << std::endl;
	Grid	*grid2 = new Grid(grid);
	grid = *grid2;
	std::cout << grid;
	return (0);
}


