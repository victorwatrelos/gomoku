#ifndef LINEDATA
# define LINEDATA

# include "../Board.hpp"
# include "BoardUtilities.hpp"
# include "AbstractLineData.hpp"

class				LineData : public AbstractLineData
{
	public:
		LineData(void);
		LineData(const LineData &obj);
		LineData &operator=(const LineData &p);
		virtual ~LineData(void);
	protected:
		void		_endOfSeries(void);
	private:
		int			_getStoneScore(void);
};

#endif
