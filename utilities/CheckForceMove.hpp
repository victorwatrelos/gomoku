#ifndef CHECKFORCEMOVE
# define CHECKFORCEMOVE

# include "../Board.hpp"
# include "BoardUtilities.hpp"
# include "AbstractLineData.hpp"

class				CheckForceMove : public AbstractLineData
{
	public:
		CheckForceMove(void);
		CheckForceMove(const CheckForceMove &obj);
		CheckForceMove &operator=(const CheckForceMove &p);
		virtual ~CheckForceMove(void);
		int				getForcedMove(void);
		void			init(const Board::Point &color, const Board *b);
		void			addPoint(const Board::Point &color, int pos);
	protected:
		void		_endOfSeries(void);
	private:
		std::unordered_set<int>	_lstMove;
		int						_forcedMove;
		int						_pos;
};

#endif
