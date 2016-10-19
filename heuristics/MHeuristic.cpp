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
	this->_b = &(b->getBoard());
	this->_color = color;
	this->_getLines();
	return this->_totScore;
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
	this->_totScore += std::pow(4, this->_lineData.nbCons);
	bzero(&(this->_lineData), sizeof(t_lineData));
}

void					MHeuristic::_analysePoint(const Board::Point &p)
{
	if (p == this->_color)
	{
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

void					MHeuristic::_getLines()
{
	this->_currentLine = LineType::HORI;
	this->_getHLines();
}
