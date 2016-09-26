#include "Board.hpp"

Board::Board(void) : _board(GRID_SIZE, Board::Point::EMPTY)
{
	this->_board[0] = PEMPTY;
	this->_board[19] = Board::Point::WHITE;
	this->_board[38] = Board::Point::BLACK;
	this->_board[57] = PEMPTY;
	this->_board[76] = Board::Point::WHITE;
	this->_board[95] = PEMPTY;

	this->_board[22] = Board::Point::WHITE;
	this->_board[41] = Board::Point::WHITE;

	this->_board[0] = PEMPTY;
	this->_board[1] = Board::Point::WHITE;
	this->_board[2] = PEMPTY;
	this->_board[3] = PEMPTY;
	this->_board[4] = Board::Point::WHITE;
	this->_board[5] = PEMPTY;

	this->_board[0] = PEMPTY;
	this->_board[20] = Board::Point::WHITE;
	this->_board[40] = PEMPTY;
	this->_board[60] = Board::Point::WHITE;
	this->_board[80] = PEMPTY;
	this->_board[100] = PEMPTY;

	this->_board[18] = PEMPTY;
	this->_board[36] = Board::Point::WHITE;
	this->_board[54] = PEMPTY;
	this->_board[72] = Board::Point::WHITE;
	this->_board[90] = PEMPTY;
	this->_board[108] = PEMPTY;
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
