#include "SimpleHeuristic.hpp"

SimpleHeuristic::SimpleHeuristic(void) {}

SimpleHeuristic::SimpleHeuristic(const SimpleHeuristic & rhs)
{
	*this = rhs;
}

SimpleHeuristic::~SimpleHeuristic(void) {}

SimpleHeuristic&		SimpleHeuristic::operator=(const SimpleHeuristic & rhs)
{
	(void)rhs;
	return *this;
}

int						SimpleHeuristic::eval(Board *b, Board::Point color)
{
	return b->getScore(color);
}
