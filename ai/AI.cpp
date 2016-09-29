#include "AI.hpp"

AI::AI(void)
{
	this->_h = nullptr;
	this->_player_color = PEMPTY;
}

AI::AI(const AI & rhs)
{
	*this = rhs;
}

AI::AI(AbstractHeuristic *h, Board::Point &color) : _h(h), _player_color(color)
{
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

int			AI::minimax(Board *node, int depth, bool player)
{
	int		val, bestValue = 0;
	std::vector<Board*>	children;

	if (depth == 0)
		return (this->_h->eval(node));

	if (player)
	{
		bestValue = -100000;
		children = node->expand(this->_player_color);
		this->nb_state += children.size();
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
		children = node->expand(Board::getOppColor(this->_player_color));
		this->nb_state += children.size();
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
