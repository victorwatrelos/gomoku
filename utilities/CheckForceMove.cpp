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

void	CheckForceMove::setBoards(std::vector<Board> *lstBoard)
{
	this->_lstBoard = lstBoard;
}

void					CheckForceMove::_insertMoveIfValid(int pos)
{
	if (this->_board->isMoveValid(pos, this->_playerColor))
	{
		this->_lstBoard->push_back(Board(*this->_board));
		this->_lstBoard->back().setMove(pos, this->_playerColor);
	}
}


void					CheckForceMove::_endOfSeries(void)
{
	if (this->_nbCons <= 0)
		return ;
	if (this->_nbCons == 4)
	{
		if (this->_interSpace > 0)
			this->_insertMoveIfValid(this->_posInter);
		else
		{
			if (this->_endingSpace)
				this->_insertMoveIfValid(this->_posEnd);
			if (this->_startingSpace)
				this->_insertMoveIfValid(this->_posStart);
		}
	}
	if (this->_nbCons == 3)
	{
		if (this->_interSpace > 0)
			this->_insertMoveIfValid(this->_posInter);
		if (this->_endingSpace)
			this->_insertMoveIfValid(this->_posEnd);
		if (this->_startingSpace)
			this->_insertMoveIfValid(this->_posStart);
	}
	this->_startingSpace = false;
	this->_endingSpace = false;
	this->_nbCons = 0;
}
