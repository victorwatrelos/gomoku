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
	//StdOutDisplay		t;

	this->_b = &(b->getBoard());
	this->_color = color;
	this->_lineData.init(color, this->_b);
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
			this->_lineData.endOfSeries();
		}
		this->_lineData.addPoint((*this->_b)[i], i);
	}
	this->_lineData.endOfSeries();
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
	this->_lineData.endOfSeries();
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
		this->_lineData.endOfSeries();
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

void					MHeuristic::LineData::init(const Board::Point &color, const std::vector<Board::Point> *grid)
{
	this->_playerColor = color;
	this->_nbCons = 0;
	this->_tot = 0;
	this->_grid = grid;
}

void					MHeuristic::LineData::endOfSeries(void)
{
	int		tmpScore;

	if (this->_nbCons <= 0)
		return ;
	tmpScore = std::pow(4, this->_nbCons);
	if (this->_currentColor == this->_playerColor)
		this->_tot += tmpScore;
	else
		this->_tot -= tmpScore;
		
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
	const MHeuristic::t_dir		&dir = this->_getDir();
	int		x = pos % GRID_LENGTH;
	int		y = pos / GRID_LENGTH;
	int		nbSpace = 0;

	while (MHeuristic::coordValid(x, y))
	{
		if (this->_currentColor == (*this->_grid)[x + y * GRID_LENGTH] || this->_currentColor == Board::Point::EMPTY)
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
	while (MHeuristic::coordValid(x, y))
	{
		if (this->_currentColor == (*this->_grid)[x + y * GRID_LENGTH] || this->_currentColor == Board::Point::EMPTY)
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

void					MHeuristic::LineData::addPoint(const Board::Point &p, int pos)
{
	if (this->_currentColor == p)
	{
		this->_nbCons++;
		return ;
	}
	if (p != Board::Point::EMPTY)
	{
		this->endOfSeries();
		if (this->_hasPlace(pos))
		{
			this->_currentColor = p;
			this->_nbCons = 1;
		}
	 } else {
	 	 this->endOfSeries();
	 }
}

void					MHeuristic::LineData::setDir(LineType dir)
{
	this->_dir = dir;
}

int						MHeuristic::LineData::getScore(void)
{
	return this->_tot;
}
