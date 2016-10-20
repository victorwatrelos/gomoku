#ifndef LINEDATA
# define LINEDATA

# include "../Board.hpp"
# include "BoardUtilities.hpp"
# include "AbstractLineData.hpp"

class				LineData : public AbstractLineData
{
	public:
		enum class LineType : char {HORI, VERT, DIAG1, DIAG2};
		typedef struct		s_dir {
			int x;
			int	y;
		}					t_dir;
		LineData(void);
		LineData(const LineData &obj);
		LineData &operator=(const LineData &p);
		virtual ~LineData(void);
	protected:
		void		_endOfSeries(void);
};

#endif
