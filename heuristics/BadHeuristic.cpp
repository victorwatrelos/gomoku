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

int					BadHeuristic::eval(Board *b, Board::Point color)
{
	int				rd;

	(void)b;
	(void)color;
	std::srand(std::time(0));
	rd = std::rand() % 100000;
	return (rd);
}
