#include "MHeuristic.hpp"

MHeuristic::MHeuristic(void) {
}

MHeuristic::MHeuristic(const MHeuristic & rhs)
{
	*this = rhs;
}

MHeuristic::~MHeuristic(void) {}

MHeuristic&		MHeuristic::operator=(const MHeuristic & rhs)
{
	(void)rhs;
	return *this;
}

#include "../display/StdOutDisplay.hpp"

int						MHeuristic::eval(Board *b, Board::Point color)
{
	StdOutDisplay		t;

	this->_b = &(b->getBoard());
	this->_color = color;
	this->_lineData.init(color, b);
	this->_oppColor = Board::getOppColor(color);
	this->_getLines();
	//std::cout << "for: " << ((color == Board::Point::BLACK) ? "Black" : "White") << std::endl;
	//t.displayBoard(*b);
	//std::cout << "My score: " << this->_lineData.getScore() << " b: " << b->getScore(color) << std::endl;
	return this->_lineData.getScore();
	//return b->getScore(color);
}

void					MHeuristic::_getHLines()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (i % GRID_LENGTH == 0 && i > 0)
		{
			this->_lineData.endOfLine();
		}
		this->_lineData.addPoint((*this->_b)[i], i);
	}
	this->_lineData.endOfLine();
}

bool		MHeuristic::coordValid(int x, int y)
{
	if (x < 0 || x >= GRID_LENGTH || y < 0 || y > GRID_LENGTH)
		return (false);
	return (true);
}

void		MHeuristic::_browseDLine(int startX, int startY, const t_dir &dir)
{
	int			x, y, pos;

	x = startX;
	y = startY;
	while (this->coordValid(x, y))
	{
		pos = x + y * GRID_LENGTH;
		this->_lineData.addPoint((*this->_b)[pos], pos);
		x += dir.x;
		y += dir.y;
	}
	this->_lineData.endOfLine();
}

void		MHeuristic::_getD1Lines()
{
	int			startX, startY = 0;
	t_dir		dir = {-1, 1};

	for (startX = 0; startX < GRID_LENGTH; startX++)
		this->_browseDLine(startX, startY, dir);
	startX = GRID_LENGTH - 1;
	for (startY = 1; startY < GRID_LENGTH; startY++)
		this->_browseDLine(startX, startY, dir);
}

void		MHeuristic::_getD2Lines()
{
	int			startX, startY = 0;
	t_dir		dir = {1, 1};

	for (startX = 0; startX < GRID_LENGTH; startX++)
		this->_browseDLine(startX, startY, dir);
	startX = 0;
	for (startY = 1; startY < GRID_LENGTH; startY++)
		this->_browseDLine(startX, startY, dir);
}

void					MHeuristic::_getVLines()
{
	int		pos;

	for (int x = 0; x < GRID_LENGTH; x++)
	{
		for (int y = 0; y < GRID_LENGTH; y++)
		{
			pos = y * GRID_LENGTH + x;
			this->_lineData.addPoint((*this->_b)[pos], pos);
		}
		this->_lineData.endOfLine();
	}
}

void					MHeuristic::_getLines()
{
	this->_lineData.setDir(LineType::HORI);
	this->_getHLines();
	this->_lineData.setDir(LineType::VERT);
	this->_getVLines();
	this->_lineData.setDir(LineType::DIAG1);
	this->_getD1Lines();
	this->_lineData.setDir(LineType::DIAG2);
	this->_getD2Lines();
}

void					MHeuristic::LineData::init(const Board::Point &color, const Board *b)
{
	this->_playerColor = color;
	this->_nbCons = 0;
	this->_tot = 0;
	this->_grid = &(b->getBoard());
	this->_board = b;
}

std::string		MHeuristic::LineData::_getColor(const Board::Point &col)
{
	if (col == Board::Point::BLACK)
		return "Black";
	if (col == Board::Point::WHITE)
		return "White";
	return "Empty";
}

void					MHeuristic::LineData::_display(void)
{
	std::cout << "current col: " << this->_getColor(this->_currentColor) << std::endl
		<< " player col: " << this->_getColor(this->_currentColor) << std::endl
		<< " interSpace: " << this->_interSpace << std::endl
		<< " last is space: " << this->_lastIsSpace << std::endl
		<< " first is space: " << this->_startingSpace << std::endl
		<< " ending space: " << this->_endingSpace << std::endl
		<< " nb cons: " << this->_nbCons << std::endl;
}

void					MHeuristic::LineData::endOfLine(void)
{
	this->_endOfSeries();
	this->_endingSpace = false;
	this->_startingSpace = false;
	this->_lastIsSpace = false;
	this->_interSpace = 0;

}

void					MHeuristic::LineData::_endOfSeries(void)
{
	int		tmpScore;

	if (this->_nbCons <= 0)
		return ;
	//this->_display();

	if (this->_nbCons == 3 
			&& ((this->_startingSpace && this->_endingSpace)
				|| (this->_startingSpace && this->_interSpace > 0)
				|| (this->_endingSpace && this->_interSpace > 0))
			)
	{
		tmpScore = std::pow(5, 6);
	}
	else if (this->_nbCons == 4 && this->_startingSpace && this->_endingSpace)
	{
		if (this->_currentColor == this->_playerColor)
			tmpScore = 100'000;
		else
			tmpScore = 100'000;
	}
	else if (this->_nbCons >= 5)
	{
		tmpScore = 75'000;
	}
	else
	{
		tmpScore = std::pow(5, this->_nbCons);
	}

	if (this->_currentColor == this->_playerColor)
		this->_tot += tmpScore / 2;
	else
		this->_tot -= tmpScore;
	this->_lastIsSpace = false;
	this->_startingSpace = false;
	this->_endingSpace = false;
	this->_nbCons = 0;
}

const MHeuristic::t_dir			MHeuristic::LineData::_getDir(void) const
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
			return {-1, -1};
	}
}

bool				MHeuristic::LineData::_hasPlace(int pos)
{
	const MHeuristic::t_dir		dir = this->_getDir();
	int		startX, startY, x, y;
	int		nbSpace = 1;
	Board::Point	colPos;
	startX = x = pos % GRID_LENGTH;
	startY = y = pos / GRID_LENGTH;

	x -= dir.x;
	y -= dir.y;
	while (MHeuristic::coordValid(x, y))
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
	while (MHeuristic::coordValid(x, y))
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

void					MHeuristic::LineData::_addSpace(void)
{
	if (this->_nbCons > 0)
	{
		if (this->_interSpace > 0)
		{
			this->_endingSpace = true;
			this->_endOfSeries();
			this->_startingSpace = true;
		}
		else
			this->_interSpace++;
	}
	else
		this->_startingSpace = true;
	this->_lastIsSpace = true;
}

void					MHeuristic::LineData::_addPointSameColor(void)
{
	this->_nbCons++;
	this->_lastIsSpace = false;
}

void					MHeuristic::LineData::_addPointOtherColor(const Board::Point &p, int pos)
{
	this->_endOfSeries();
	if (this->_hasPlace(pos))
	{
		this->_currentColor = p;
		this->_nbCons = 1;
	}
	this->_lastIsSpace = false;
}

void					MHeuristic::LineData::addPoint(const Board::Point &p, int pos)
{
	if (this->_currentColor == p)
		this->_addPointSameColor();
	else if (p != Board::Point::EMPTY)
		this->_addPointOtherColor(p, pos);
	else
	 	 this->_addSpace();
}

void					MHeuristic::LineData::setDir(LineType dir)
{
	this->_dir = dir;
}

int						MHeuristic::LineData::getScore(void)
{
	return this->_tot;
}
