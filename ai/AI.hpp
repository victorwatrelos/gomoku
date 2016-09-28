#ifndef AI_HPP
# define AI_HPP

# include "State.hpp"

class						AI
{
	public:
							AI(void);
							AI(const AI & rhs);
		virtual				~AI(void);
		AI&					operator=(const AI & rhs);

		int					minimax(State *node, int depth, bool player);

};


#endif
