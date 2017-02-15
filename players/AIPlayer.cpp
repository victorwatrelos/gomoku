#include "AIPlayer.hpp"

AIPlayer::AIPlayer(void) 
	: _lineData(new CheckForceMove()), _browseBoard(this->_lineData) {
	this->_name = "AIPlayer";
	this->_color = Board::Point::EMPTY;
}

AIPlayer::AIPlayer(const AIPlayer & rhs)
{
	*this = rhs;
}

AIPlayer::AIPlayer(const std::string &name, const Board::Point &color, int aiLevel)
	: _lineData(new CheckForceMove()), _browseBoard(this->_lineData)
{
	this->_name = name;
	this->_color = color;
	this->_h = new MHeuristic();
	this->_ai = new AI(this->_h, this->_color, aiLevel);
	this->_ai->setInitialDepth(AIPlayer::INITIAL_DEPTH);
}

AIPlayer::~AIPlayer(void) {}

std::string			AIPlayer::getInfo(void) const
{
	std::stringstream ss;

	ss << "Maximal depth: " << this->_ai->getMaxDepth();
	return ss.str();
}

std::string			AIPlayer::getLastTime(void) const
{
	return this->_getStrTime(this->_ai->getLastTime());
}

AIPlayer&			AIPlayer::operator=(const AIPlayer & rhs)
{
	this->_name = rhs._name;
	this->_color = rhs._color;
	this->_h = rhs._h;
	this->_ai = rhs._ai;
	return *this;
}

void				AIPlayer::_expandPoints(Board::Point color, int pos, std::unordered_set<int> &dups, const Board &b, int depth)
{
	int				i, j, index;
	int				m, n;

	i = pos % GRID_LENGTH - depth;
	j = pos / GRID_LENGTH - depth;
	m = pos % GRID_LENGTH + depth + 1;
	n = pos / GRID_LENGTH + depth + 1;
	
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	if (m > GRID_LENGTH)
		m = GRID_LENGTH;
	if (n > GRID_LENGTH)
		n = GRID_LENGTH;

	while (i < m)
	{
		for (int jj = j ; jj < n ; jj++)
		{
			index = b.getIndex(i, jj);
			if (dups.find(index) == dups.end())
			{
				if (b.isMoveValid(index, color))
					dups.insert(index);
			}
		}
		i++;
	}
}

int						AIPlayer::getMove(const Board &board)
{
	Board				new_board;
	int					best_pos = 0;
	std::unordered_set<int>		dups;
	std::vector<Board::Point>	b = board.getBoard();

	this->_ai->nb_state = 0;
	best_pos = this->_ai->ID(board, this->_color);

	std::cout << "history size : " << this->_ai->getHistorySize() << std::endl;
	std::cout << "TT size : " << this->_ai->getTTSize() << std::endl;
	std::cout << "nb state explored : " << this->_ai->nb_state << std::endl;
	return best_pos;
}
