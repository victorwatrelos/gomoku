#include "AI.hpp"

AI::AI(void)
{
}

AI::AI(const AI & rhs)
{
	*this = rhs;
}

AI::~AI(void)
{
}

AI&			AI::operator=(const AI & rhs)
{
	(void)rhs;
	return *this;
}

/*
 * 		MINIMAX
 */

int			AI::minimax(State *node, int depth, bool player)
{
	int		val, bestValue = 0;
	std::vector<State*>	children;

	if (depth == 0)
		return (node->eval());

	if (player)
	{
		bestValue = -100000;
		children = node->expand();
		for (auto child : children) {
			val = this->minimax(child, depth - 1, false);
			if (val > bestValue)
				bestValue = val;
		}
		for (auto &i : children)
			delete i;
		children.clear();
	}
	else
	{
		bestValue = 100000;
		children = node->expand();
		for (auto child : children) {
			val = this->minimax(child, depth - 1, true);
			if (val < bestValue)
				bestValue = val;
		}
		for (auto &i : children)
			delete i;
		children.clear();
	}
	return (bestValue);
}
