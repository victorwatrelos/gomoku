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
		const std::unordered_set<int>	&getForcedMove(void);
		virtual void			init(const Board::Point &color, const Board *b);
	protected:
		void		_endOfSeries(void);
	private:
		std::unordered_set<int>	_lstMove;
		void					_insertMoveIfValid(int pos);
		int						_removeNPos(int mult);
};

#endif
