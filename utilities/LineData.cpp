#include "LineData.hpp"

LineData::LineData(void) {
}

LineData::~LineData(void)
{
}

void					LineData::_endOfSeries(void)
{
	int		tmpScore;
	int		nbSpace = 0;

	if (this->_nbCons <= 0)
		return ;
	//this->_display();

	if (this->_nbCons >= 5)
	{
		tmpScore = 100'000;
		//tmpScore = std::pow(4, 5);
	}
	else
	{
		tmpScore = std::pow(4, this->_nbCons);
		if (this->_nbCons >= 3)
		{
			if (this->_startingSpace)
				nbSpace++;
			if (this->_endingSpace)
				nbSpace++;
			if (this->_interSpace == 0)
				tmpScore += std::pow(4, nbSpace);
		}
		else
		{
			if (this->_interSpace > 0)
			{
				tmpScore -= 16;
			}
		}
	}

	//std::cout << "tmp score: " << tmpScore << std::endl;
	if (this->_currentColor == this->_playerColor)
		this->_tot += tmpScore;
	else
		this->_tot -= tmpScore;
	this->_startingSpace = false;
	this->_endingSpace = false;
	this->_nbCons = 0;
}
