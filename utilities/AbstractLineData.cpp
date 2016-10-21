#include "AbstractLineData.hpp"

AbstractLineData::AbstractLineData(void) {
}

AbstractLineData::~AbstractLineData(void)
{
}

void					AbstractLineData::init(const Board::Point &color, const Board *b)
{
	this->_playerColor = color;
	this->_nbCons = 0;
	this->_tot = 0;
	this->_grid = &(b->getBoard());
	this->_board = b;
}

std::string		AbstractLineData::_getColor(const Board::Point &col)
{
	if (col == Board::Point::BLACK)
		return "Black";
	if (col == Board::Point::WHITE)
		return "White";
	return "Empty";
}

void					AbstractLineData::_display(void)
{
	std::cout << "current col: " << this->_getColor(this->_currentColor) << std::endl
		<< " player col: " << this->_getColor(this->_currentColor) << std::endl
		<< " interSpace: " << this->_interSpace << std::endl
		<< " inter pos: " << this->_posInter << std::endl
		<< " last is space: " << this->_lastIsSpace << std::endl
		<< " first is space: " << this->_startingSpace << std::endl
		<< " ending space: " << this->_endingSpace << std::endl
		<< " nb cons: " << this->_nbCons << std::endl;
}

void					AbstractLineData::endOfLine(void)
{
	this->_endOfSeries();
	this->_endingSpace = false;
	this->_startingSpace = false;
	this->_lastIsSpace = false;
	this->_interSpace = 0;

}

const AbstractLineData::t_dir			AbstractLineData::_getDir(void) const
{
	switch (this->_dir)
	{
		case LineType::HORI:
			return {1, 0};
		case LineType::VERT:
			return {0, 1};
		case LineType::DIAG1:
			return {-1, 1};
		case LineType::DIAG2:
			return {1, 1};
	}
}


bool				AbstractLineData::_hasPlace(int pos)
{
	const t_dir		dir = this->_getDir();
	int		startX, startY, x, y;
	int		nbSpace = 1;
	Board::Point	colPos;
	startX = x = pos % GRID_LENGTH;
	startY = y = pos / GRID_LENGTH;

	x -= dir.x;
	y -= dir.y;
	while (BoardUtilities::coordValid(x, y))
	{
		colPos = (*this->_grid)[x + y * GRID_LENGTH];
		if (/*this->_board->isMoveValid(pos, this->_currentColor) 
			&& */(this->_currentColor == colPos
				|| colPos == Board::Point::EMPTY)
			)
		{
			nbSpace++;
			if (nbSpace >= 5)
				return (true);
			x -= dir.x;
			y -= dir.y;
		}
		else
			break;
	}
	x = startX + dir.x;
	y = startY + dir.y;
	while (BoardUtilities::coordValid(x, y))
	{
		colPos = (*this->_grid)[x + y * GRID_LENGTH];
		if (this->_currentColor == colPos
				|| colPos == Board::Point::EMPTY)
		{
			nbSpace++;
			if (nbSpace >= 5)
				return (true);
			x += dir.x;
			y += dir.y;
		}
		else
			break;
	}
	//std::cout << "Here (x: " << startX << ", y: " << startY << ")" << std::endl;
	return false;
}

void					AbstractLineData::_addSpace(void)
{
	if (this->_nbCons > 0)
	{
		if (this->_interSpace > 0)
		{
			if (this->_lastIsSpace)
				this->_interSpace--;
			this->_endingSpace = true;
			this->_endOfSeries();
			this->_startingSpace = true;
		}
		else
		{
			this->_interSpace++;
			this->_posInter = this->_pos;
		}
	}
	else
		this->_startingSpace = true;
	this->_lastIsSpace = true;
}

void					AbstractLineData::_addPointSameColor(void)
{
	this->_nbCons++;
	this->_lastIsSpace = false;
}

void					AbstractLineData::_addPointOtherColor(const Board::Point &p, int pos)
{
	this->_endOfSeries();
	this->_currentColor = p;
	if (this->_hasPlace(pos))
	{
		this->_nbCons = 1;
	}
	if (this->_lastIsSpace)
		this->_startingSpace = true;
	this->_lastIsSpace = false;
}

void					AbstractLineData::addPoint(const Board::Point &p, int pos)
{
	this->_pos = pos;
	if (this->_nbCons > 0 && this->_currentColor == p)
		this->_addPointSameColor();
	else if (p != Board::Point::EMPTY)
		this->_addPointOtherColor(p, pos);
	else
	 	 this->_addSpace();
}

void					AbstractLineData::setDir(LineType dir)
{
	this->_dir = dir;
}

int						AbstractLineData::getScore(void)
{
	return this->_tot;
}