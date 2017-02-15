#ifndef AIPLAYER_HPP
# define AIPLAYER_HPP

# include "../ai/AI.hpp"
# include "AbstractPlayer.hpp"
# include "../heuristics/AbstractHeuristic.hpp"
# include "../utilities/CheckForceMove.hpp"
# include "../heuristics/MHeuristic.hpp"
# include <sstream>

class						AIPlayer : public AbstractPlayer
{
	public:
		static const int	INITIAL_DEPTH = 2;
							AIPlayer(void);
							AIPlayer(const AIPlayer & rhs);
							AIPlayer(const std::string &name, const Board::Point &color, int aiLevel = 1);
		virtual				~AIPlayer(void);
		AIPlayer&			operator=(const AIPlayer & rhs);
		int					getMove(const Board &board);
		std::string			getInfo(void) const;
		std::string			getLastTime(void) const;

	private:
		void				_expandPoints(Board::Point color, int pos, std::unordered_set<int> &dups, const Board &b, int depth);
		void				_fillNextMoves(std::unordered_set<int> &dups, const Board &b);

		AI					*_ai;
		AbstractHeuristic	*_h;
		CheckForceMove		*_lineData;
		BrowseBoard			_browseBoard;

};

#endif
