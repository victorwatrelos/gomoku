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

int			AI::minimaxAB(Board *node, int depth, int A, int B, bool player)
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
			val = this->minimaxAB(child, depth - 1, A, B, false);
			if (val > bestValue)
				bestValue = val;
			if (bestValue > A)
				A = bestValue;
			if (B <= A)
				break;
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
			val = this->minimaxAB(child, depth - 1, A, B, true);
			if (val < bestValue)
				bestValue = val;
			if (bestValue < B)
				B = bestValue;
			if (B <= A)
				break;
		}
		for (auto &i : children)
			delete i;
		children.clear();
	}
	return (bestValue);
}

int				AI::negamax(Board *node, int depth, int A, int B, int player)
{
	int		val, bestValue = 0;
	std::vector<Board*>	children;

	if (depth == 0)
		return (this->_h->eval(node) * player);
	if (player == 1)
		children = node->expand(this->_player_color);
	else
		children = node->expand(Board::getOppColor(this->_player_color));
	this->nb_state += children.size();
	bestValue = -100000;
	for (auto child : children) {
		val = -1 * this->negamax(child, depth - 1, -1 * B, -1 * A, -1 * player);
		if (val > bestValue)
			bestValue = val;
		if (val > A)
			A = val;
		if (A >= B)
			break;
	}
	for (auto &i : children)
		delete i;
	children.clear();
	return (bestValue);
}
