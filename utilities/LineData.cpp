#include "LineData.hpp"

LineData::LineData(void) {
}

LineData::~LineData(void)
{
}

int						LineData::_getStoneScore(void)
{
	int		tmpNbStone = 0;
	int		whiteStoneScore = 0;
	int		blackStoneScore = 0;

	if ((tmpNbStone = this->_board->getWhiteCapturedStone()) > 0)
	{
//		if (tmpNbStone >= 10)
//			whiteStoneScore = 100'000;
//		else
			whiteStoneScore = std::pow(4, tmpNbStone) + 256;
	}
	if ((tmpNbStone = this->_board->getBlackCapturedStone()) > 0)
	{
//		if (tmpNbStone >= 10)
//			blackStoneScore = 100'000;
//		else
			blackStoneScore = std::pow(4, tmpNbStone) + 256;
	}
	if (this->_playerColor == Board::Point::WHITE)
		return blackStoneScore - whiteStoneScore;
	else
		return whiteStoneScore - blackStoneScore;
}

void					LineData::init(const Board::Point &color, const Board *b)
{
	AbstractLineData::init(color, b);
	
	this->_tot += this->_getStoneScore();
}

void					LineData::_endOfSeries(void)
{
	int		tmpScore;
	int		nbSpace = 0;

	if (this->_nbCons <= 0)
		return ;

	/*
	if (this->_nbCons >= 5)
	{
		std::cout << "WINN" << std::endl;
		tmpScore = 100'000;
	}
	else
	{
	*/
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
//	}

	if (this->_currentColor == this->_playerColor)
		this->_tot += tmpScore;
	else
		this->_tot -= tmpScore;
	this->_startingSpace = false;
	this->_endingSpace = false;
	this->_nbCons = 0;
}
