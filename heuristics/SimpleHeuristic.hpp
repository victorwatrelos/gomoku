#ifndef SIMPLEHEURISTIC_HPP
# define SIMPLEHEURISTIC_HPP

# include "AbstractHeuristic.hpp"

class					SimpleHeuristic : public AbstractHeuristic
{
	public:
						SimpleHeuristic(void);
						SimpleHeuristic(const SimpleHeuristic & rhs);
		virtual			~SimpleHeuristic(void);
		SimpleHeuristic&	operator=(const SimpleHeuristic & rhs);

		int				eval(Board *b);
};

#endif
