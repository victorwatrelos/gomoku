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

Board    &Board::operator=(const Board &p)
{
	this->getBoard() = p.getBoard();
	return *this;
}

std::vector<Board::Point>			Board::getBoard(void) const
{
	return (this->_board);
}

bool						Board::isMoveValid(int pos) const
{
	if (pos < 0 || pos >= GRID_SIZE)
		return false;
	return true;
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
	return false;
}

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
				index = i * GRID_LENGTH + j;
			else
				index = j * GRID_LENGTH + i;
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
				streak = 0;
			else if (curr == last)
				streak++;
			if (streak == 4)
				return true;
			last = curr;
			j++;
		}
		i++;
	}
	return false;
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
				index = i * GRID_LENGTH + j;
			else
				index = j * GRID_LENGTH + i;
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
				streak = 0;
			else if (curr == last)
				streak++;
			if (streak == 4)
				return true;
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
				index = i * GRID_LENGTH + j;
			else	
				index = j * GRID_LENGTH + i;
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
				streak = 0;
			else if (curr == last)
				streak++;
			if (streak == 4)
				return true;
			last = curr;
			i--;
			j++;
		}
		a--;
	}
	return (false);
}
