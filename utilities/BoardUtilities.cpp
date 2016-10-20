#include "BoardUtilities.hpp"

bool	BoardUtilities::coordValid(int x, int y)
{
	if (x < 0 || x >= GRID_LENGTH || y < 0 || y >= GRID_LENGTH)
		return (false);
	return (true);
}
