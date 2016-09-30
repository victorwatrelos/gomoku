#ifndef AI_HPP
# define AI_HPP

# include "../Board.hpp"
# include "../heuristics/AbstractHeuristic.hpp"

class						AI
{
	public:
							AI(void);
							AI(const AI & rhs);
							AI(AbstractHeuristic *h, Board::Point &color);
		virtual				~AI(void);
		AI&					operator=(const AI & rhs);

		int					minimax(Board *node, int depth, const Board::Point &player);

		int					nb_state = 0;

	private:
		AbstractHeuristic	*_h;
		Board::Point		_player_color;
};


#endif
