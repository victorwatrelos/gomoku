#ifndef AIPLAYER_HPP
# define AIPLAYER_HPP

# include "AI.hpp"
# include "AbstractPlayer.hpp"
# include "AbstractHeuristic.hpp"

class						AIPlayer
{
	public:
							AIPlayer(void);
							AIPlayer(const AIPlayer & rhs);
							AIPlayer(const std::string &name, const Board::Point &color);
		virtual				~AIPlayer(void);
		AIPlayer&			operator=(const AIPlayer & rhs);
		int					getMove();

	private:
		AbstractHeuristic	*_h;
};

#endif
