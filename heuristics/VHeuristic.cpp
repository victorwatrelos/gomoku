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

void		VHeuristic::_addPointForLine(bool isLastEmpty = false)
{
	if (this->_lineData.cons > 0 && !(!(isLastEmpty && this->_lineData.lastEmpty) && this->_lineData.totStone < 5))
	{
		this->_totPoints += (std::pow(4, this->_lineData.cons) + (this->_lineData.empty + 1) / 2);
	}
	bzero(&(this->_lineData), sizeof(t_lineData));
}

void		VHeuristic::_parsePointOfLine(const Board::Point &b)
{
	bool	empty = (b == Board::Point::EMPTY);
	if (b == this->_color) {
		this->_lineData.cons++;
		this->_lineData.lastEmpty = false;
		this->_totStone++;
	} else if (empty && !this->_lineData.lastEmpty) {
		this->_lineData.lastEmpty = true;
		this->_lineData.empty++;
		this->_totStone++;
	} else {
		this->_addPointForLine(empty);
	}
}

void		VHeuristic::_getLine(const std::vector<Board::Point> &b)
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (i % GRID_LENGTH == 0 && i > 0)
		{
			this->_addPointForLine();
		}
		this->_parsePointOfLine(b[i]);
	}
	this->_addPointForLine();
}

int			VHeuristic::eval(Board *b, const Board::Point &color, bool neg)
{
	//this->_startTimer();
	this->_totPoints = 0;
	this->_color = color;
	this->_getLine(b->getBoard());
	//res = b->getScore();
	//this->_endTimer();
	if (this->display) {
		std::cout << "Current: " << this->_totPoints << std::endl;
	}
	return (this->_totPoints);

}
