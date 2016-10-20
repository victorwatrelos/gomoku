#include "CheckForceMove.hpp"

CheckForceMove::CheckForceMove(void) {
}

CheckForceMove::~CheckForceMove(void)
{
}

void			CheckForceMove::init(const Board::Point &color, const Board *b)
{
	this->_forcedMove = -1;
	AbstractLineData::init(color, b);
}

void					CheckForceMove::addPoint(const Board::Point &color, int pos)
{
	this->_pos = pos;
	AbstractLineData::addPoint(color, pos);
}

int						CheckForceMove::getForcedMove(void)
{
	return this->_forcedMove;
}

void					CheckForceMove::_endOfSeries(void)
{
	if (this->_nbCons == 4)
	{
		if (this->_startingSpace && !this->_endingSpace && this->_interSpace == 0)
		{
			this->_forcedMove = this->_pos - 5;
		}
		if (this->_endingSpace && !this->_startingSpace && this->_interSpace == 0)
		{
			this->_forcedMove = this->_pos - 1;
		}
	}
}
