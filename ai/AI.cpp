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


#include "../display/StdOutDisplay.hpp"
int			AI::minimax(Board *node, int depth, const Board::Point &player)
{
	int		val, bestValue = 0;
	std::vector<Board*>	children;

	if (node->isWinningBoard())
	{
		/*
			StdOutDisplay	disp;
			std::cout << "Depth: " << depth << std::endl;
			disp.displayBoard(*node);
			std::cout << "AWinning board, depth: " << depth << std::endl;
			*/

		if (depth == DEPTH)
			return (900000);
		if (depth == (DEPTH - 1))
			return (800000);
	}
	if (depth == 0 || node->isWinningBoard())
		return (this->_h->eval(node, player, depth));

	if (player == this->_player_color)
	{
		bestValue = -1000000;
		children = node->expand(Board::getOppColor(this->_player_color));
		this->nb_state += children.size();
		for (auto child : children) {
			val = this->minimax(child, depth - 1, Board::getOppColor(player));
			if (val > bestValue)
				bestValue = val;
		}
		for (auto &i : children)
			delete i;
		children.clear();
	}
	else
	{
		bestValue = 1000000;
		children = node->expand(Board::getOppColor(this->_player_color));
		this->nb_state += children.size();
		for (auto child : children) {
			val = this->minimax(child, depth - 1, Board::getOppColor(player));
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
	Board::Point		col;

	//std::cout << "Depth: " << depth << " player: " << player << std::endl;
	if (node->isWinningBoard())
	{
		if (depth == DEPTH)
			return (900000);
		if (depth == (DEPTH - 1))
			return (800000);
	}
	if (player)
		col = this->_player_color;
	else
		col = Board::getOppColor(this->_player_color);
	if (depth == 0)
		return (this->_h->eval(node, col, depth));

	if (player)
	{
		bestValue = -1000000;
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
		bestValue = 1000000;
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
	Board::Point		color;

	if (node->isWinningBoard())
	{
		StdOutDisplay	disp;
		disp.displayBoard(*node);
		if (depth == DEPTH)
			return (300000);
		if (depth == (DEPTH - 1))
			return (200000);
		return (100000);
	}
	if (player == 1)
		color = this->_player_color;
	else
		color = Board::getOppColor(this->_player_color);
	if (depth == 0)
		return this->_h->eval(node, this->_player_color, depth) * player;

	children = node->expand(color);
	this->nb_state += children.size();
	bestValue = -1000000;
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
