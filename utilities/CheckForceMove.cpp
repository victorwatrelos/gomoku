#include "CheckForceMove.hpp"

CheckForceMove::CheckForceMove(void) {
}

CheckForceMove::~CheckForceMove(void)
{
}

void			CheckForceMove::init(const Board::Point &color, const Board *b)
{
	this->_lstMove.clear();
	AbstractLineData::init(color, b);
}

const std::unordered_set<int>	&CheckForceMove::getForcedMove(void)
{
	return this->_lstMove;
}

void					CheckForceMove::_insertMoveIfValid(int pos)
{
	if (this->_board->isMoveValid(pos, this->_playerColor))
	{
		this->_lstMove.insert(pos);
	}
}

int						CheckForceMove::_removeNPos(int mult)
{
	int	x = this->_pos % GRID_LENGTH;
	int y = this->_pos / GRID_LENGTH;
	auto dir = this->_getDir();

	x -= dir.x * mult;
	y -= dir.y * mult;
	return x + y * GRID_LENGTH;
}

void					CheckForceMove::_endOfSeries(void)
{
	if (BoardUtilities::coordValid(this->_pos)
			&& (*this->_grid)[this->_pos] == Board::Point::EMPTY)
	{
		this->_endingSpace = true;
	}
	if (this->_nbCons == 4)
	{
		if (this->_interSpace > 0)
		{
			this->_insertMoveIfValid(this->_posInter);
		}
		else if (this->_startingSpace)
		{
			if (!this->_endingSpace)
				this->_insertMoveIfValid(this->_removeNPos(5));
			else
				this->_insertMoveIfValid(this->_removeNPos(6));
		}
		else if (this->_endingSpace && this->_interSpace == 0)
		{
			this->_insertMoveIfValid(this->_removeNPos(1));
		}
	} else if (this->_nbCons == 3 && this->_startingSpace && this->_endingSpace)
	{
		if (this->_interSpace > 0)
		{
			this->_insertMoveIfValid(this->_posInter);
		}
		else
		{
			this->_insertMoveIfValid(this->_removeNPos(5));
			this->_insertMoveIfValid(this->_removeNPos(1));
		}
	}
	this->_startingSpace = false;
	this->_endingSpace = false;
	this->_nbCons = 0;
}
