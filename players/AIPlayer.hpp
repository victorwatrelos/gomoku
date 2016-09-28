#ifndef AIPLAYER_HPP
# define AIPLAYER_HPP

# include "../ai/AI.hpp"
# include "AbstractPlayer.hpp"
# include "../heuristics/AbstractHeuristic.hpp"
// to be deleted
# include "../heuristics/BadHeuristic.hpp"
# include "../heuristics/SimpleHeuristic.hpp"

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
		AbstractHeuristic	*_h;
		AI					_ai;

};

#endif
