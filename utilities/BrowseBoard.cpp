#include "BrowseBoard.hpp"

BrowseBoard::BrowseBoard(void) 
{
	this->_lineData = new LineData();
}

BrowseBoard::BrowseBoard(AbstractLineData *lineData) 
{
	this->_lineData = lineData;
}

BrowseBoard::BrowseBoard(const BrowseBoard & rhs)
{
	*this = rhs;
}

BrowseBoard::~BrowseBoard(void) {
}

BrowseBoard&		BrowseBoard::operator=(const BrowseBoard & rhs)
{
	(void)rhs;
	return *this;
}

//# include "../display/StdOutDisplay.hpp"

int						BrowseBoard::browse(const Board &b, Board::Point color)
{
	//StdOutDisplay		t;

	//std::cout << "Line data addr in browse board: " << this->_lineData << std::endl;
	this->_b = &(b.getBoard());
	this->_color = color;
	this->_lineData->init(color, &b);
	this->_oppColor = Board::getOppColor(color);
	this->_getLines();
	//std::cout << "for: " << ((color == Board::Point::BLACK) ? "Black" : "White") << std::endl;
	//t.displayBoard(*b);
	//std::cout << "My score: " << this->_lineData->getScore() << " b: " << b->getScore(color) << std::endl;
	return this->_lineData->getScore();
	//return b->getScore(color);
}

void					BrowseBoard::_getHLines()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (i % GRID_LENGTH == 0 && i > 0)
		{
			this->_lineData->endOfLine();
		}
		this->_lineData->addPoint((*this->_b)[i], i);
	}
	this->_lineData->endOfLine();
}


void		BrowseBoard::_browseDLine(int startX, int startY, const AbstractLineData::t_dir &dir)
{
	int			x, y, pos;

	x = startX;
	y = startY;
	while (BoardUtilities::coordValid(x, y))
	{
		pos = x + y * GRID_LENGTH;
		this->_lineData->addPoint((*this->_b)[pos], pos);
		x += dir.x;
		y += dir.y;
	}
	this->_lineData->endOfLine();
}

void		BrowseBoard::_getD1Lines()
{
	int			startX, startY = 0;
	AbstractLineData::t_dir		dir = {-1, 1};

	for (startX = 0; startX < GRID_LENGTH; startX++)
		this->_browseDLine(startX, startY, dir);
	startX = GRID_LENGTH - 1;
	for (startY = 1; startY < GRID_LENGTH; startY++)
		this->_browseDLine(startX, startY, dir);
}

void		BrowseBoard::_getD2Lines()
{
	int			startX, startY = 0;
	AbstractLineData::t_dir		dir = {1, 1};

	for (startX = 0; startX < GRID_LENGTH; startX++)
		this->_browseDLine(startX, startY, dir);
	startX = 0;
	for (startY = 1; startY < GRID_LENGTH; startY++)
		this->_browseDLine(startX, startY, dir);
}

void					BrowseBoard::_getVLines()
{
	int		pos;

	for (int x = 0; x < GRID_LENGTH; x++)
	{
		for (int y = 0; y < GRID_LENGTH; y++)
		{
			pos = y * GRID_LENGTH + x;
			this->_lineData->addPoint((*this->_b)[pos], pos);
		}
		this->_lineData->endOfLine();
	}
}

void					BrowseBoard::_getLines()
{
	this->_lineData->setDir(AbstractLineData::LineType::HORI);
	this->_getHLines();
	this->_lineData->setDir(AbstractLineData::LineType::VERT);
	this->_getVLines();
	this->_lineData->setDir(AbstractLineData::LineType::DIAG1);
	this->_getD1Lines();
	this->_lineData->setDir(AbstractLineData::LineType::DIAG2);
	this->_getD2Lines();
}

