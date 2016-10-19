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

int						MHeuristic::eval(Board *b, Board::Point color)
{
	this->_reset();
	this->_b = &(b->getBoard());
	this->_color = color;
	this->_oppColor = Board::getOppColor(color);
	this->_getLines();
	//std::cout << "My score: " << this->_totScore << " b: " << b->getScore(color) << std::endl;
	this->_resetLineData();
	return this->_totScore;
	//return b->getScore(color);
}

void					MHeuristic::_reset()
{
	this->_totScore = 0;
	this->_resetLineData();
}

void					MHeuristic::_resetLineData()
{
	if (this->_lineData.nbCons <= 0)
		return ;
	//std::cout << "nb cons: " << this->_lineData.nbCons << std::endl;
	this->_totScore += std::pow(4, this->_lineData.nbCons);
	bzero(&(this->_lineData), sizeof(t_lineData));
}

void					MHeuristic::_analysePoint(const Board::Point &p)
{
	if (p == this->_color)
	{
		//std::cout << "Color match" << std::endl;
		this->_lineData.nbCons++;
		return ;
	}
	this->_resetLineData();

}

void					MHeuristic::_getHLines()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (i % GRID_LENGTH == 0 && i > 0)
		{
			this->_resetLineData();
		}
		this->_analysePoint((*this->_b)[i]);
	}
}

bool		MHeuristic::_coordValid(int x, int y)
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
	while (this->_coordValid(x, y))
	{
		pos = x + y * GRID_LENGTH;
		this->_analysePoint((*this->_b)[pos]);
		x += dir.x;
		y += dir.y;
	}
	this->_resetLineData();
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
			this->_analysePoint((*this->_b)[pos]);
		}
		this->_resetLineData();
	}
}

void					MHeuristic::_getLines()
{
	this->_currentLine = LineType::HORI;
	this->_getHLines();
	this->_currentLine = LineType::VERT;
	this->_getVLines();
	this->_currentLine = LineType::DIAG1;
	this->_getD1Lines();
	this->_currentLine = LineType::DIAG2;
	this->_getD2Lines();
}
