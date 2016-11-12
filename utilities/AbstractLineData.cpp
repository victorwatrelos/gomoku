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
	std::cout << "current col: " << this->_getColor(this->_currentColor) <<  " -- "
		<< " player col: " << this->_getColor(this->_currentColor) <<   " -- "
		<< " interSpace: " << this->_interSpace << " -- "
		<< " inter pos: " << this->_posInter
		<< "(" << this->_posInter % GRID_LENGTH + 1<< "," << this->_posInter / GRID_LENGTH + 1<< ")"
		<< ") -- "
		<< " last is space: " << this->_lastIsSpace <<   " -- "
		<< " first is space: " << this->_startingSpace << "(" << this->_posStart % GRID_LENGTH + 1 << ","
			<< this->_posStart / GRID_LENGTH + 1 << ") -- "
		<< " ending space: " << this->_endingSpace << "(" << this->_posEnd % GRID_LENGTH + 1 << "," 
			<< this->_posEnd / GRID_LENGTH + 1 << ") -- "
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
	return false;
}

int						AbstractLineData::_removeNPos(int pos, int mult)
{
	int	x = pos % GRID_LENGTH;
	int y = pos / GRID_LENGTH;
	auto dir = this->_getDir();

	x -= dir.x * mult;
	y -= dir.y * mult;
	return x + y * GRID_LENGTH;
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
			if (this->_lastIsSpace)
				this->_posEnd = this->_removeNPos(this->_pos, 1);
			else
				this->_posEnd = this->_pos;
			this->_endOfSeries();
			this->_startingSpace = true;
			this->_posStart = this->_pos;
		}
		else
		{
			this->_interSpace++;
			this->_posInter = this->_pos;
		}
	}
	else
	{
		this->_startingSpace = true;
		this->_posStart = this->_pos;
	}
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
	{
		this->_posStart = this->_removeNPos(pos, 1);
		this->_startingSpace = true;
	}
	this->_lastIsSpace = false;
}

/*
static std::string		getColor(const Board::Point &p)
{
	if (p == Board::Point::BLACK)
		return "X";
	if (p == Board::Point::WHITE)
		return "O";
	return "_";
}
*/

void					AbstractLineData::addPoint(const Board::Point &p, int pos)
{
//	std::cout << "Color: " << getColor(p) << " pos: " << pos << std::endl;
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
