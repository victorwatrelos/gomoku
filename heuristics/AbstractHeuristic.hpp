#ifndef ABSTRACTHEURISTIC_HPP
# define ABSTRACTHEURISTIC_HPP

# include "../Board.hpp"

class						AbstractHeuristic
{
	public:
		virtual int			eval(Board *b, const Board::Point &color, int depth) = 0;
};

#endif
