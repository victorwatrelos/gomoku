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
	printTT(dur);
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
	if (this->display)
	{
		//displayLineData(this->_lineData);
	}
	if (this->_lineData.cons > 0 || this->_lineData.totCons > 0)
	{
		if (this->_lineData.empty)
			emptyPoint = 1;
		else
			emptyPoint = 0;
		this->_totPoints += (std::pow(4, this->_lineData.cons) + this->_lineData.totCons + emptyPoint);
	}
	bzero(&(this->_lineData), sizeof(t_lineData));
}

void		VHeuristic::_parsePointOfLine(const Board::Point &b)
{
	bool	empty = (b == Board::Point::EMPTY);
	if (b == this->_color) {
		this->_lineData.cons++;
		this->_lineData.lastEmpty = false;
		this->_lineData.totStone++;
	} else if (empty && !this->_lineData.lastEmpty) {
		this->_lineData.lastEmpty = true;
		this->_lineData.empty++;
		this->_lineData.totStone++;
		if (this->_lineData.cons)
		{
			this->_lineData.totCons += std::pow(4, this->_lineData.cons);
			this->_lineData.cons = 0;
		}
	} else {
		this->_addPointForLine(empty);
	}
}

bool		VHeuristic::_checkHoriPos(const std::vector<Board::Point> &b, int pos)
{
	int		nbFree = 0;
	int		min = pos - pos % GRID_LENGTH;
	if (pos == 0)
		min = 0;
	for (int i = pos; i >= min; i--)
	{
		if (!(b[i] == Board::Point::EMPTY || b[i] == this->_color))
		{
			break ;
		}
		nbFree++;
		if (nbFree >= 5)
			return true;
	}
	nbFree--;
	for (int i = pos; (i % GRID_LENGTH > 0 || i == 0); i++)
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

void		VHeuristic::_getLine(const std::vector<Board::Point> &b)
{
	//this->_parsePointOfLine(b[0]);
	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (i % GRID_LENGTH == 0 && i > 0)
		{
			this->_addPointForLine();
		}
		if (this->_checkHoriPos(b, i))
			this->_parsePointOfLine(b[i]);
	}
	this->_addPointForLine();
}

int			VHeuristic::eval(Board *b, const Board::Point &color, bool neg)
{
	std::string turn;
	int			res, totfirst, totsecond;
	bzero(&(this->_lineData), sizeof(t_lineData));
	(void)neg;
	//this->_startTimer();
	this->_totPoints = 0;
	this->_color = color;
	this->_oppColor = Board::getOppColor(color);
	this->_getLine(b->getBoard());
	std::cout << "--------------------------------" << std::endl << std::endl;
	res = this->_totPoints;
	totfirst = this->_totPoints;
	this->_totPoints = 0;
	this->_color = this->_oppColor;
	this->_oppColor = Board::getOppColor(this->_color);
	this->_getLine(b->getBoard());
	res -= this->_totPoints;
	totsecond = this->_totPoints;
	//res = b->getScore();
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
	return (this->_totPoints);

}
