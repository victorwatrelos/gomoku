#include "LineData.hpp"

LineData::LineData(void) {
}

LineData::~LineData(void)
{
}

void					LineData::_endOfSeries(void)
{
	int		tmpScore;

	if (this->_nbCons <= 0)
		return ;
	//this->_display();

	if (this->_nbCons == 4
			&& (this->_startingSpace || this->_endingSpace))
	{
		tmpScore = 100'000;
	}
	else if (this->_nbCons == 4 &&
			(this->_startingSpace || this->_endingSpace || this->_interSpace))
	{
		tmpScore = 100'000;
	}
	else if (this->_nbCons >= 5)
	{
		tmpScore = 100'000;
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
