#include "LineData.hpp"

LineData::LineData(void) {
}

LineData::~LineData(void)
{
}

static int		my_pow(int n)
{
	switch (n)
	{
		case 0:
			return 1;
		case 1:
			return 4;
		case 2:
			return 16;
		case 3:
			return 64;
		case 4:
			return 256;
		case 5:
			return 1024;
		case 6:
			return 4096;
		default:
			return std::pow(4, n);
	};
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
		whiteStoneScore = my_pow(tmpNbStone) + 256;
	}
	if ((tmpNbStone = this->_board->getBlackCapturedStone()) > 0)
	{
		//		if (tmpNbStone >= 10)
		//			blackStoneScore = 100'000;
		//		else
		blackStoneScore = my_pow(tmpNbStone) + 256;
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
	int		nbSpace;

	if (this->_nbCons <= 0)
		return ;
	nbSpace = 0;

	tmpScore = my_pow(this->_nbCons);
	if (this->_nbCons >= 3)
	{
		if (this->_startingSpace)
			nbSpace++;
		if (this->_endingSpace)
			nbSpace++;
		if (this->_interSpace == 0)
			tmpScore += my_pow(nbSpace);
	}
	else
	{
		if (this->_interSpace > 0)
		{
			tmpScore -= 16;
		}
	}

	if (this->_currentColor == this->_playerColor)
		this->_tot += tmpScore;
	else
		this->_tot -= tmpScore;
	this->_startingSpace = false;
	this->_endingSpace = false;
	this->_nbCons = 0;
}
