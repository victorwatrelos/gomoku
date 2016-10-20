#ifndef AIPLAYER_HPP
# define AIPLAYER_HPP

# include "../ai/AI.hpp"
# include "AbstractPlayer.hpp"
# include "../heuristics/AbstractHeuristic.hpp"
# include "../utilities/CheckForceMove.hpp"
// to be deleted
# include "../heuristics/BadHeuristic.hpp"
# include "../heuristics/SimpleHeuristic.hpp"
# include "../heuristics/MHeuristic.hpp"

class						AIPlayer : public AbstractPlayer
{
	public:
							AIPlayer(void);
							AIPlayer(const AIPlayer & rhs);
							AIPlayer(const std::string &name, const Board::Point &color);
		virtual				~AIPlayer(void);
		AIPlayer&			operator=(const AIPlayer & rhs);
		int					getMove(const Board &board);

	private:
		void				_expandPoints(Board::Point color, int pos, std::unordered_set<int> &dups, const Board &b, int depth);
		void				_fillNextMoves(std::unordered_set<int> &dups, const Board &b);

		AI					*_ai;
		AbstractHeuristic	*_h;
		BrowseBoard			_browseBoard;
		CheckForceMove		*_lineData;

};

#endif
