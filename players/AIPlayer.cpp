#include "AIPlayer.hpp"

AIPlayer::AIPlayer(void) {
	this->_name = "AIPlayer";
	this->_color = PEMPTY;
}

AIPlayer::AIPlayer(const AIPlayer & rhs)
{
	*this = rhs;
}

AIPlayer::AIPlayer(const std::string &name, const Board::Point &color)
{
	this->_name = name;
	this->_color = color;
	this->_h = new VHeuristic();
	this->_ai = new AI(this->_h, this->_color);
}

AIPlayer::~AIPlayer(void) {}

AIPlayer&			AIPlayer::operator=(const AIPlayer & rhs)
{
	this->_name = rhs._name;
	this->_color = rhs._color;
	this->_h = rhs._h;
	this->_ai = rhs._ai;
	return *this;
}

int					AIPlayer::getMove(const Board &board)
{
	Board				new_board;
	int					best_h = -1;
	int					best_pos = 0;
	int					h_value;

	this->_ai->nb_state = 0;
	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (board.isMoveValid(pos, this->_color))
		{
			new_board = board;
			new_board.setMove(pos, this->_color);
			h_value = this->_ai->minimax(&new_board, 2, this->_color);
			if (h_value > best_h)
			{
				best_h = h_value;
				best_pos = pos;
			}
		}
	}
	std::cout << "nb state explored : " << this->_ai->nb_state << std::endl;
	return best_pos;
}
