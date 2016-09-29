#include "Board.hpp"

Board::Board(void) : _board(GRID_SIZE, Board::Point::EMPTY)
{
}

Board::Board(const Board &obj)
{
	*this = obj;
}

Board::~Board(void)
{
}

Board    					&Board::operator=(const Board &p)
{
	this->_board = p.getBoard();
	return *this;
}

const std::vector<Board::Point>&		Board::getBoard(void) const
{
	return (const_cast<const std::vector<Board::Point>&>(this->_board));
}

Board::Point						Board::getOppColor(Point player_color)
{
	if (player_color == Point::WHITE)
		return Point::BLACK;
	return Point::WHITE;
}

void						Board::setMove(int pos, Board::Point color)
{
	if (pos < 0 || pos >= GRID_SIZE)
		return ;
	this->_board[pos] = color;
}

bool						Board::isMoveValid(int pos, Board::Point color) const
{
	if (pos < 0 || pos >= GRID_SIZE)
		return (false);
	else if (this->_board[pos] != Board::Point::EMPTY)
		return (false);
	else if (this->_checkMoveInCapture(pos, color))
		return (false);
	else if (this->_checkDoubleThree(pos, color))
		return (false);
	return (true);
}

bool						Board::isWinningBoard(void) const
{
	if (this->_checkWinningLine(true))
		return (true);
	if (this->_checkWinningLine(false))
		return (true);
	if (this->_checkWinningDiag(true))
		return (true);
	if (this->_checkWinningDiag(false))
		return (true);
	if (this->_checkWinningBackDiag(true))
		return (true);
	if (this->_checkWinningBackDiag(false))
		return (true);
	return (false);
}

int							Board::getIndex(int i, int j) const
{
	return (j * GRID_LENGTH + i);
}

/*
 *		CHECK FOR WINNING BOARD FUNCTIONS
 */

bool						Board::_checkWinningLine(bool isRow) const
{
	int						i, j, index;
	int						streak;
	Board::Point			curr, last;

	i = 0;
	last = Board::Point::EMPTY;
	while (i < GRID_LENGTH)
	{
		j = 0;
		streak = 0;
		while (j < GRID_LENGTH)
		{
			if (isRow)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
				streak = 0;
			else if (curr == last)
				streak++;
			if (streak == 4)
				return (true);
			last = curr;
			j++;
		}
		i++;
	}
	return (false);
}

bool						Board::_checkWinningBackDiag(bool down) const
{
	int						a, i, j, index;
	int						streak;
	Board::Point			curr, last;

	last = Board::Point::EMPTY;
	a = 0;
	if (down)
		a++;
	while (a < GRID_LENGTH - 1)
	{
		i = a;
		j = 0;
		streak = 0;
		while (i < GRID_LENGTH)
		{
			if (down)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
				streak = 0;
			else if (curr == last)
				streak++;
			if (streak == 4)
				return (true);
			last = curr;
			i++;
			j++;
		}
		a++;
	}
	return (false);
}

bool						Board::_checkWinningDiag(bool down) const
{
	int						a, i, j, index;
	int						streak = 0;
	Board::Point			curr, last;

	last = Board::Point::EMPTY;
	a = GRID_LENGTH - 1;
	while (a > 0)
	{
		i = a;
		j = 0;
		if (down)
			j++;
		streak = 0;
		while (i > 0)
		{
			if (down)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
				streak = 0;
			else if (curr == last)
				streak++;
			if (streak == 4)
				return (true);
			last = curr;
			i--;
			j++;
		}
		a--;
	}
	return (false);
}

/*
 *		CHECK FOR DOUBLE THREE FUNCTIONS
 */

bool					Board::_checkDoubleThree(int pos, Board::Point color) const
{
	int					*three;

	if ((three = this->_checkThreeLine(pos, color, false)) != nullptr)
	{
		for (int i = 0 ; i < 3 ; i++) {
			if (three[i] == pos)
				continue ;
			if ((this->_checkThreeLine(three[i], color, true)) != nullptr)
				return (true);
			if ((this->_checkThreeBackDiag(three[i], color)) != nullptr)
				return (true);
			if ((this->_checkThreeDiag(three[i], color)) != nullptr)
				return (true);
		}
	}
	if ((three = this->_checkThreeLine(pos, color, true)) != nullptr)
	{
		for (int i = 0 ; i < 3 ; i++) {
			if (three[i] == pos)
				continue ;
			if ((this->_checkThreeLine(three[i], color, false)) != nullptr)
				return (true);
			if ((this->_checkThreeBackDiag(three[i], color)) != nullptr)
				return (true);
			if ((this->_checkThreeDiag(three[i], color)) != nullptr)
				return (true);
		}
	}
	if ((three = this->_checkThreeDiag(pos, color)) != nullptr)
	{
		for (int i = 0 ; i < 3 ; i++) {
			if (three[i] == pos)
				continue ;
			if ((this->_checkThreeLine(three[i], color, true)) != nullptr)
				return (true);
			if ((this->_checkThreeLine(three[i], color, false)) != nullptr)
				return (true);
			if ((this->_checkThreeBackDiag(three[i], color)) != nullptr)
				return (true);
		}
	}
	if ((three = this->_checkThreeBackDiag(pos, color)) != nullptr)
	{
		for (int i = 0 ; i < 3 ; i++) {
			if (three[i] == pos)
				continue ;
			if ((this->_checkThreeLine(three[i], color, true)) != nullptr)
				return (true);
			if ((this->_checkThreeLine(three[i], color, false)) != nullptr)
				return (true);
			if ((this->_checkThreeDiag(three[i], color)) != nullptr)
				return (true);
		}
	}
	return (false);
}

void					Board::_resetThreeCheck(int **three, int *it, int *space) const
{
	(*three)[0] = 0;
	(*three)[1] = 0;
	(*three)[2] = 0;
	*it = 0;
	*space = 0;
}

int						*Board::_checkThreeLine(int pos, Board::Point color, bool isHoriz) const
{
	int					*three = new int[3];
	int					it = 0;
	int					space = 0;
	int					i, j, index;
	int					stop;
	Board::Point		curr, last;

	if (isHoriz)
	{
		i = pos / GRID_LENGTH;
		j = pos % GRID_LENGTH - 3;
		stop = (pos % GRID_LENGTH) + 5;
	}
	else
	{
		i = pos % GRID_LENGTH;
		j = pos / GRID_LENGTH - 3;
		stop = (pos / GRID_LENGTH) + 5;
	}
	if (j < -2)
		return nullptr;
	else if (j <= 0)
		j = 1;
	if (stop >= GRID_LENGTH)
		stop = GRID_LENGTH;
	index = this->getIndex(i, j - 1);
	last = this->_board[index];
	while (j < stop)
	{
		if (isHoriz)
			index = this->getIndex(j, i);
		else
			index = this->getIndex(i, j);
		if (index != pos)
			curr = this->_board[index];
		else
			curr = color;
		if (it == 3 && curr == PEMPTY)
			return three;
		else if (last == color && curr == PEMPTY && space < 2)
			space++;
		else if (((last == PEMPTY && curr == color) || (last == color && curr == color)) && space < 2)
			three[it++] = index;
		else if ((last == PEMPTY && curr == PEMPTY) || (curr != last))
			this->_resetThreeCheck(&three, &it, &space);
		last = curr;
		j++;
	}
	return nullptr;
}

int						*Board::_checkThreeBackDiag(int pos, Board::Point color) const
{
	int					*three = new int[3];
	int					it = 0;
	int					space = 0;
	int					i, j, index;
	int					stopI, stopJ;
	Board::Point		curr, last;

	i = pos % GRID_LENGTH + 3;
	j = pos / GRID_LENGTH - 3;
	stopI = pos % GRID_LENGTH - 5;
	stopJ = (pos / GRID_LENGTH) + 5;
	if (j < -2 || i > GRID_LENGTH + 1)
		return nullptr;
	if (j <= 0)
		j = 1;
	if (i > GRID_LENGTH - 2)
		i = GRID_LENGTH - 2;
	if (stopI < 0)
		stopI = 0;
	if (stopJ >= GRID_LENGTH)
		stopJ = GRID_LENGTH;
	index = this->getIndex(i - 1, j - 1);
	last = this->_board[index];
	while (i >= stopI && j < stopJ)
	{
		index = this->getIndex(i, j);
		if (index != pos)
			curr = this->_board[index];
		else
			curr = color;
		if (it == 3 && curr == PEMPTY)
			return three;
		else if (last == color && curr == PEMPTY && space < 2)
			space++;
		else if (((last == PEMPTY && curr == color) || (last == color && curr == color)) && space < 2)
			three[it++] = index;
		else if ((last == PEMPTY && curr == PEMPTY) || (curr != last))
			this->_resetThreeCheck(&three, &it, &space);
		last = curr;
		i--;
		j++;
	}
	return nullptr;
}

int						*Board::_checkThreeDiag(int pos, Board::Point color) const
{
	int					*three = new int[3];
	int					it = 0;
	int					space = 0;
	int					i, j, index;
	int					stopI, stopJ;
	Board::Point		curr, last;

	i = pos % GRID_LENGTH - 3;
	j = pos / GRID_LENGTH - 3;
	stopI = (pos % GRID_LENGTH) + 5;
	stopJ = (pos / GRID_LENGTH) + 5;
	if (j < -2 || i < -2)
		return nullptr;
	if (j <= 0)
		j = 1;
	if (i <= 0)
		i = 1;
	if (stopI >= GRID_LENGTH)
		stopI = GRID_LENGTH;
	if (stopJ >= GRID_LENGTH)
		stopJ = GRID_LENGTH;
	index = this->getIndex(i - 1, j - 1);
	last = this->_board[index];
	while (i < stopI && j < stopJ)
	{
		index = this->getIndex(i, j);
		if (index != pos)
			curr = this->_board[index];
		else
			curr = color;
		if (it == 3 && curr == PEMPTY)
			return three;
		else if (last == color && curr == PEMPTY && space < 2)
			space++;
		else if (((last == PEMPTY && curr == color) || (last == color && curr == color)) && space < 2)
			three[it++] = index;
		else if ((last == PEMPTY && curr == PEMPTY) || (curr != last))
			this->_resetThreeCheck(&three, &it, &space);
		last = curr;
		i++;
		j++;
	}
	return nullptr;
}

/*
 *			CHECK FOR MOVE IN CAPTURE
 */

bool					Board::_checkMoveInCapture(int pos, Board::Point color) const
{
	int					i, j;
	int					index1, index2, index3;
	Board::Point		opp;

	if (color == Board::Point::WHITE)
		opp = Board::Point::BLACK;
	else
		opp = Board::Point::WHITE;
	i = pos % GRID_LENGTH;
	j = pos / GRID_LENGTH;

	index1 = this->getIndex(i - 1, j - 1);
	index2 = this->getIndex(i + 1, j + 1);
	index3 = this->getIndex(i + 2, j + 2);
	if (this->_board[index1] == opp && this->_board[index2] == color && this->_board[index3] == opp)
		return (true);
	index1 = this->getIndex(i - 2, j - 2);
	index2 = this->getIndex(i - 1, j - 1);
	index3 = this->getIndex(i + 1, j + 1);
	if (this->_board[index1] == opp && this->_board[index2] == color && this->_board[index3] == opp)
		return (true);

	index1 = this->getIndex(i - 2, j + 2);
	index2 = this->getIndex(i - 1, j + 1);
	index3 = this->getIndex(i + 1, j - 1);
	if (this->_board[index1] == opp && this->_board[index2] == color && this->_board[index3] == opp)
		return (true);
	index1 = this->getIndex(i - 1, j + 1);
	index2 = this->getIndex(i + 1, j - 1);
	index3 = this->getIndex(i + 2, j - 2);
	if (this->_board[index1] == opp && this->_board[index2] == color && this->_board[index3] == opp)
		return (true);

	index1 = this->getIndex(i - 2, j);
	index2 = this->getIndex(i - 1, j);
	index3 = this->getIndex(i + 1, j);
	if (this->_board[index1] == opp && this->_board[index2] == color && this->_board[index3] == opp)
		return (true);
	index1 = this->getIndex(i - 1, j);
	index2 = this->getIndex(i + 1, j);
	index3 = this->getIndex(i + 2, j);
	if (this->_board[index1] == opp && this->_board[index2] == color && this->_board[index3] == opp)
		return (true);

	index1 = this->getIndex(i, j + 2);
	index2 = this->getIndex(i, j + 1);
	index3 = this->getIndex(i, j - 1);
	if (this->_board[index1] == opp && this->_board[index2] == color && this->_board[index3] == opp)
		return (true);
	index1 = this->getIndex(i, j + 1);
	index2 = this->getIndex(i, j - 1);
	index3 = this->getIndex(i, j - 2);
	if (this->_board[index1] == opp && this->_board[index2] == color && this->_board[index3] == opp)
		return (true);

	return (false);
}

/*
 * TEST
 */


int							Board::_checkStreakLine(bool isRow) const
{
	int						i, j, index;
	int						streak;
	Board::Point			curr, last;
	int						score = 0;

	i = 0;
	last = Board::Point::EMPTY;
	while (i < GRID_LENGTH)
	{
		j = 0;
		streak = 0;
		while (j < GRID_LENGTH)
		{
			if (isRow)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
			{
				score += std::pow(4, streak);
				streak = 0;
			}
			else if (curr == last)
				streak++;
			if (streak == 4)
			{
				score += std::pow(4, streak);
				streak = 0;
			}
			last = curr;
			j++;
		}
		i++;
	}
	if (streak != 0)
		score += std::pow(4, streak);
	return (score);
}

int							Board::_checkStreakBackDiag(bool down) const
{
	int						a, i, j, index;
	int						streak;
	Board::Point			curr, last;
	int						score = 0;

	last = Board::Point::EMPTY;
	a = 0;
	if (down)
		a++;
	while (a < GRID_LENGTH - 1)
	{
		i = a;
		j = 0;
		streak = 0;
		while (i < GRID_LENGTH)
		{
			if (down)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
			{
				score += std::pow(4, streak);
				streak = 0;
			}
			else if (curr == last)
				streak++;
			if (streak == 4)
			{
				score += std::pow(4, streak);
				streak = 0;
			}
			last = curr;
			i++;
			j++;
		}
		a++;
	}
	if (streak != 0)
		score += std::pow(4, streak);
	return (score);
}

int							Board::_checkStreakDiag(bool down) const
{
	int						a, i, j, index;
	int						streak = 0;
	Board::Point			curr, last;
	int						score = 0;

	last = Board::Point::EMPTY;
	a = GRID_LENGTH - 1;
	while (a > 0)
	{
		i = a;
		j = 0;
		if (down)
			j++;
		streak = 0;
		while (i > 0)
		{
			if (down)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
			{
				score += std::pow(4, streak);
				streak = 0;
			}
			else if (curr == last)
				streak++;
			if (streak == 4)
			{
				score += std::pow(4, streak);
				streak = 0;
			}
			last = curr;
			i--;
			j++;
		}
		a--;
	}
	if (streak != 0)
		score += std::pow(4, streak);
	return (score);
}

int					Board::getScore()
{
	int				score = 0;

	score += this->_checkStreakLine(true);
	score += this->_checkStreakDiag(true);
	score += this->_checkStreakBackDiag(true);
	score += this->_checkStreakLine(false);
	score += this->_checkStreakDiag(false);
	score += this->_checkStreakBackDiag(false);
	return score;
}

/*
std::vector<Board*>		Board::expand(Point color)
{
	std::vector<Board*>	st;
	Board				*new_board;

	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (this->isMoveValid(pos, color))
		{
			new_board = new Board(*this);
			new_board->setMove(pos, color);
			st.push_back(new_board);
		}
	}
	return st;
}
*/

std::vector<Board*>		Board::expand(Point color)
{
	std::vector<Board*>	st;
	int							set = 0;

	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (this->_board[pos] != PEMPTY)
		{
			this->_expandPoint(st, color, pos);
			set++;
		}
	}
	if (set == 0)
		this->_expandPoint(st, color, 180);
	return st;
}

void				Board::_expandPoint(std::vector<Board *> &st, Board::Point color, int pos)
{
	int				i, j, index;
	int				m, n;
	Board			*new_board;

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
			index = this->getIndex(i, j);
			if (this->isMoveValid(index, color))
			{
				new_board = new Board(*this);
				new_board->setMove(index, color);
				st.push_back(new_board);
			}
			j++;
		}
		i++;
	}
}
