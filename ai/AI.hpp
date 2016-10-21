#ifndef AI_HPP
# define AI_HPP

# include "../Board.hpp"
# include "../heuristics/AbstractHeuristic.hpp"
# include "../utilities/CheckForceMove.hpp"
# include "../utilities/BrowseBoard.hpp"

# define TIMEP				std::chrono::high_resolution_clock::time_point	

class						AI
{
	public:
							AI(void);
							AI(const AI & rhs);
							AI(AbstractHeuristic *h, Board::Point &color);
		virtual				~AI(void);
		AI&					operator=(const AI & rhs);

		int					minimax(Board *node, int depth, bool player);
		int					minimaxAB(Board *node, int depth, int A, int B, bool player);
		int					negamax(Board *node, int depth, int A, int B, int player);

		int					nb_state = 0;

		void				resetTimer(void);
		void				startTimer();
		void				addTime(long long &dur);
		TIMEP				getTime();
		long long			getInt(TIMEP start, TIMEP end);
		void				printTime(long long dur, std::string str);
		void				showTime();
		static const int	DEPTH = 3;

	private:
		const std::vector<Board *>	_expandNode(Board *node, int player, int depth);

		AbstractHeuristic	*_h;
		Board::Point		_player_color;

		long long			_t_expansion;
		long long			_t_eval;
		long long			_t_vector_clear;
		TIMEP				_timer;
		CheckForceMove		*_lineData;
		BrowseBoard			_browseBoard;
};

#endif
