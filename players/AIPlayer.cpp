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
	this->_h = new SimpleHeuristic();
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
/*
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
			h_value = this->_ai->minimax(&new_board, 2, true);
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
*/

void				expandPoints(Board::Point color, int pos, std::unordered_set<int> &dups, const Board &b)
{
	int				i, j, index;
	int				m, n;

	i = pos % GRID_LENGTH - 3;
	j = pos / GRID_LENGTH - 3;
	m = pos % GRID_LENGTH + 3;
	n = pos / GRID_LENGTH + 3;
	
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	if (m >= GRID_LENGTH)
		m = GRID_LENGTH - 1;
	if (n >= GRID_LENGTH)
		n = GRID_LENGTH - 1;

	while (i < m)
	{
		while (j < n)
		{
			index = b.getIndex(i, j);
			if (dups.find(index) == dups.end())
			{
				if (b.isMoveValid(index, color))
				{
					dups.insert(index);
				}
			}
			j++;
		}
		i++;
	}

}

int					AIPlayer::getMove(const Board &board)
{
	Board				new_board;
	int					best_h = -1;
	int					best_pos = 0;
	int					h_value;
	std::unordered_set<int>		dups;
	int					set = 0;
	std::vector<Board::Point>		bobo = board.getBoard();

	this->_ai->nb_state = 0;
	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (bobo[pos] != PEMPTY)
		{
			expandPoints(this->_color, pos, dups, board);
			set++;
		}
	}

	for (auto i : dups)
	{
		new_board = board;
		new_board.setMove(i, this->_color);
		h_value = this->_ai->minimax(&new_board, 2, true);
		if (h_value > best_h)
		{
			best_h = h_value;
			best_pos = i;
		}
	}
	std::cout << "nb state explored : " << this->_ai->nb_state << std::endl;
	return best_pos;
}
