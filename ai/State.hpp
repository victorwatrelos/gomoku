#ifndef STATE_HPP
# define STATE_HPP

# include "../Board.hpp"
# include "../heuristics/AbstractHeuristic.hpp"
# include <vector>

class							State
{
	public:
								State(void);
								State(const State & rhs);
//								State(Board::Point player_col, AbstractHeuristic *h);
								State(Board b, Board::Point player_col, AbstractHeuristic *h);
		virtual					~State(void);
		State&					operator=(const State & rhs);

		void					setBoard(Board board);
		int						eval(void);
		std::vector<State*>		expand(void);

	private:
		Board					_board;
		Board::Point			_player_col;
		AbstractHeuristic		*_h;
};

#endif
