#ifndef ABSTRACTHEURISTIC_HPP
# define ABSTRACTHEURISTIC_HPP

# include "../Board.hpp"

class						AbstractHeuristic
{
	public:
		virtual int			eval(Board *b, Board::Point color) = 0;
};

#endif
