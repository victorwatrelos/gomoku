#include "HashUtilities.hpp"

namespace HashUtilities
{

	uint64_t		getBaseHashTableEntry(int i, int j)
	{
		if (baseHashTable == nullptr)
			baseHashTable = initZorb();
		return baseHashTable[i][j];
	}

	uint64_t		**initZorb()
	{
		uint64_t	**zorbTable = new uint64_t*[GRID_SIZE];

		struct timeval									tv;
		gettimeofday(&tv, NULL);
		boost::mt19937									randGen(tv.tv_usec);
		boost::uniform_int<uint64_t>					uInt64Dist(0, std::numeric_limits<uint64_t>::max());
		boost::variate_generator<boost::mt19937&, boost::uniform_int<uint64_t> >	getRand(randGen, uInt64Dist);

		for (int i = 0 ; i < GRID_SIZE; i++)
		{
			zorbTable[i] = new uint64_t[2];
			for (int j = 0 ; j < 2 ; j++)
			{
				zorbTable[i][j] = getRand();
			}
		}
		return zorbTable;
	}

	/*
uint64_t		AI::_hashBoard(const Board *node) const
{
	int			j;
	Board::Point	p;
	uint64_t	h = 0;

	for (int i = 0 ; i < GRID_SIZE ; i++)
	{
		if ((p = node->lookAt(i)) != Board::Point::EMPTY)
		{
			j = ((p == Board::Point::BLACK) ? 0 : 1);
			h = h ^ this->_baseHashTable[i][j];
		}
	}
	return (h);
}*/

}
