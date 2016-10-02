#include "VHeuristic.hpp"

VHeuristic::VHeuristic(void) {

}

VHeuristic::VHeuristic(const VHeuristic &obj) {
	*this = obj;
}

VHeuristic::~VHeuristic(void) {

}

VHeuristic    &VHeuristic::operator=(const VHeuristic &p) {
	(void)p;
	return *this;
}

static void                printTT(unsigned long int t)
{
    int             m, s, ms, us;

    m = (t / 60000000);
    s = (t / 1000000) % 60;
    ms = (t / 1000) % 1000;
    us = t % 1000;
    printf("Time taken for heuristic: %dm%ds%dms%dus\n", m, s, ms, us);
}

void		VHeuristic::_startTimer(void) {
	this->_start = std::chrono::high_resolution_clock::now();
}

void		VHeuristic::_endTimer(void) {
	std::chrono::high_resolution_clock::time_point      end;
	long long                                           dur;

	end = std::chrono::high_resolution_clock::now();
	dur = std::chrono::duration_cast<std::chrono::microseconds>( end - this->_start ).count();
	this->_time.push_back(dur);
}
void		VHeuristic::displayTime(void) {
	long long int average = std::accumulate( this->_time.begin(), this->_time.end(), 0.0)/this->_time.size(); 
	std::cout << "Average" << std::endl;
	printTT(average);
	this->_time.clear();
}
/*
static void		displayLineData(const VHeuristic::t_lineData &data)
{
	std::cout << "Cons: " << data.cons << std::endl;
	std::cout << "totCons: " << data.totCons << std::endl;
	std::cout << "empty: " << data.empty << std::endl;
	std::cout << "lastEmpty: " << data.lastEmpty << std::endl;
	std::cout << "totStone: " << data.totStone<< std::endl;
}*/

void		VHeuristic::_addPointForLine(bool isLastEmpty = false)
{
	int		emptyPoint;

	(void)isLastEmpty;
	if (this->_lineData.cons)
		this->_totPoints += (std::pow(4, this->_lineData.cons));
	bzero(&(this->_lineData), sizeof(t_lineData));
}


void		VHeuristic::_parsePointOfLine(const Board::Point &b, int pos)
{
	(void)pos;
	if (b == this->_color)
	{
		if (!this->_checkFreeMove(pos))
		{
			return ;
		}
		this->_lineData.cons++;
	} else if (b != this->_color) {
		this->_addPointForLine();
	}
}

void		VHeuristic::_getLine()
{
	this->_currentLine = LineType::HORI;
	this->_getHLine();
	/*
	this->_currentLine = LineType::VERT;
	this->_getVLine();
	this->_currentLine = LineType::DIAG1;
	this->_getD1Line();
	this->_currentLine = LineType::DIAG2;
	this->_getD2Line();
	*/
}

bool		VHeuristic::_coordValid(int x, int y)
{
	if (x < 0 || x >= GRID_LENGTH || y < 0 || y > GRID_LENGTH)
		return (false);
	return (true);
}

void		VHeuristic::_browseDLine(int startX, int startY, const t_dir &dir)
{
	int			x, y, pos;

	x = startX;
	y = startY;
	while (this->_coordValid(x, y))
	{
		pos = x + y * GRID_LENGTH;
		this->_parsePointOfLine((*this->_b)[pos], pos);
		x += dir.x;
		y += dir.y;
	}
	this->_addPointForLine();
}

void		VHeuristic::_getD1Line()
{
	int			startX, startY = 0;
	t_dir		dir = {-1, 1};

	for (startX = 0; startX < GRID_LENGTH; startX++)
		this->_browseDLine(startX, startY, dir);
	startX = GRID_LENGTH - 1;
	for (startY = 1; startY < GRID_LENGTH; startY++)
		this->_browseDLine(startX, startY, dir);
}

void		VHeuristic::_getD2Line()
{
	int			startX, startY = 0;
	t_dir		dir = {1, 1};

	for (startX = 0; startX < GRID_LENGTH; startX++)
		this->_browseDLine(startX, startY, dir);
	startX = 0;
	for (startY = 1; startY < GRID_LENGTH; startY++)
		this->_browseDLine(startX, startY, dir);
}

void		VHeuristic::_getHLine()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (i % GRID_LENGTH == 0 && i > 0)
		{
			this->_addPointForLine();
		}
		this->_parsePointOfLine((*this->_b)[i], i);
	}
	this->_addPointForLine();
}

void		VHeuristic::_getVLine()
{
	int		pos;

	for (int x = 0; x < GRID_LENGTH; x++)
	{
		for (int y = 0; y < GRID_LENGTH; y++)
		{
			pos = y * GRID_LENGTH + x;
			this->_parsePointOfLine((*this->_b)[pos], pos);
		}
		this->_addPointForLine();
	}
}

/**
 * Check if there is enough place to win in a line from a pos
 */
bool		VHeuristic::_checkFreeMove(int pos)
{
	switch (this->_currentLine) {
		case LineType::HORI:
			return this->_checkHoriPos(*this->_b, pos);
		case LineType::VERT:
			return this->_checkVertPos(*this->_b, pos);
		case LineType::DIAG1:
			return this->_checkDiagPos(*this->_b, pos, STEP_DIAG1);
		case LineType::DIAG2:
			return this->_checkDiagPos(*this->_b, pos, STEP_DIAG2);
	}
}

bool		VHeuristic::_checkDiagPos(const std::vector<Board::Point> &b, int pos, int step)
{
	int		nbFree = 1;

	for (int i = pos - 1; i >= 0; i -= step)
	{
		if (!(b[i] == Board::Point::EMPTY || b[i] == this->_color))
		{
			break ;
		}
		nbFree++;
		if (nbFree >= 5)
			return true;
	}
	for (int i = pos + 1; i < GRID_SIZE; i += step)
	{
		if (!(b[i] == Board::Point::EMPTY || b[i] == this->_color))
		{
			break ;
		}
		nbFree++;
		if (nbFree >= 5)
			return true;
	}
	return (false);
}

bool		VHeuristic::_checkHoriPos(const std::vector<Board::Point> &b, int pos)
{
	int		nbFree = 1;
	int		min = pos - pos % GRID_LENGTH;

	if (pos == 0)
		min = 0;
	for (int i = pos - 1; i >= min; i--)
	{
		if (!(b[i] == Board::Point::EMPTY || b[i] == this->_color))
		{
			break ;
		}
		nbFree++;
		if (nbFree >= 5)
			return true;
	}
	for (int i = pos + 1; (i % GRID_LENGTH > 0 || i == 0); i++)
	{
		if (!(b[i] == Board::Point::EMPTY || b[i] == this->_color))
		{
			break ;
		}
		nbFree++;
		if (nbFree >= 5)
			return true;
	}
	return false;
}

bool		VHeuristic::_checkVertPos(const std::vector<Board::Point> &b, int pos)
{
	int	tmpPos;
	int	nbFree = 0;

	for (int i = 0; i < 5; i++)
	{
		tmpPos = pos - i * GRID_LENGTH;
		if (tmpPos < 0)
			break ;
		if (b[tmpPos] != Board::Point::EMPTY && b[tmpPos] != this->_color)
		{
			break ;
		}
		nbFree++;
		if (nbFree >= 5)
			return (true);
	}
	nbFree--;
	for (int i = 0; i < 5; i++)
	{
		tmpPos = pos + i * GRID_LENGTH;
		if (tmpPos >= GRID_SIZE)
			break ;
		if (b[tmpPos] != Board::Point::EMPTY && b[tmpPos] != this->_color)
		{
			break ;
		}
		nbFree++;
		if (nbFree >= 5)
			return (true);
	}
	return (false);
}



int			VHeuristic::_getTotPoints()
{
//	if (this->_isWinning)
//		return (100000);
	return this->_totPoints;
}

int			VHeuristic::eval(Board *b, const Board::Point &color, int depth)
{

	std::string turn;
	int			res, totfirst, totsecond;

	//this->_startTimer();
	this->_depth = depth;
	this->_b = &b->getBoard();
	bzero(&(this->_lineData), sizeof(t_lineData));
	this->_isWinning = false;
	this->_totPoints = 0;
	this->_color = color;
	this->_oppColor = Board::getOppColor(color);
	this->_getLine();
	res = this->_getTotPoints();

	totfirst = this->_getTotPoints();

	this->_totPoints = 0;
	this->_isWinning = false;
	this->_color = this->_oppColor;
	this->_oppColor = Board::getOppColor(this->_color);
	this->_getLine();
	res -= this->_getTotPoints();

	totsecond = this->_getTotPoints();
	//this->_endTimer();
	if (this->display) {
		if (color == Board::Point::BLACK)
			turn = "black";
		else
			turn = "white";

		std::cout << "Turn of: " << turn << ", h: "
			<< res << " pPoint: " << turn << " " 
			<< totfirst << " , " << totsecond << std::endl;
	}
	return (res);
	/*

	//res = b->getScore();
	(void)depth;
	(void)color;
	(void)this->_depth;
	(void)this->_oppColor;
	return (b->getScore());
	*/

}
