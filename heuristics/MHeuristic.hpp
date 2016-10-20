#ifndef MHEURISTIC
# define MHEURISTIC

# include "AbstractHeuristic.hpp"
# include "../utilities/BrowseBoard.hpp"

class MHeuristic : public AbstractHeuristic, public BrowseBoard
{
	public:
		MHeuristic(void);
		MHeuristic(const MHeuristic &obj);
		MHeuristic &operator=(const MHeuristic &p);
		virtual ~MHeuristic(void);
		int				eval(Board *b, Board::Point color);
	private:
};
#endif

