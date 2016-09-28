#include "BadHeuristic.hpp"

BadHeuristic::BadHeuristic(void) {}

BadHeuristic::BadHeuristic(const BadHeuristic & rhs)
{
	*this = rhs;
}

BadHeuristic::~BadHeuristic(void) {}

BadHeuristic&		BadHeuristic::operator=(const BadHeuristic & rhs)
{
	(void)rhs;
	return *this;
}

int					BadHeuristic::eval(Board *b)
{
	int				rd;

	(void)b;
	std::srand(std::time(0));
	rd = std::rand() % GRID_SIZE;
	return (rd);
}
