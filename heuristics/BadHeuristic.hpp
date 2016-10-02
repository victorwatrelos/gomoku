#ifndef BADHEURISTIC_HPP
# define BADHEURISTIC_HPP

# include "AbstractHeuristic.hpp"
# include <cstdlib>
# include <ctime>

class					BadHeuristic : public AbstractHeuristic
{
	public:
						BadHeuristic(void);
						BadHeuristic(const BadHeuristic & rhs);
		virtual			~BadHeuristic(void);
		BadHeuristic&	operator=(const BadHeuristic & rhs);

		int				eval(Board *b, Board::Point color);
};

#endif
