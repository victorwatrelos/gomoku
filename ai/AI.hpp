#ifndef AI_HPP
# define AI_HPP

# include <sys/time.h>
# include <boost/cstdint.hpp>
# include <boost/random.hpp>
# include <unordered_map>
# include "../Board.hpp"
# include "../heuristics/AbstractHeuristic.hpp"
# include "../utilities/CheckForceMove.hpp"
# include "../utilities/BrowseBoard.hpp"

# define TIMEP				std::chrono::high_resolution_clock::time_point	

namespace			TTUtility
{
	enum Flag {EXACT = 3, LOWERBOUND = 2, UPPERBOUND = 1};

	typedef struct		s_ttEntry
	{
		int				value;
		int				pos;
		int				depth;
		Flag			flag;
		int				age;
	}					t_ttEntry;

}

class						AI
{
	public:
							AI(void);
							AI(const AI & rhs);
							AI(AbstractHeuristic *h, Board::Point &color);
		virtual				~AI(void);
		AI&					operator=(const AI & rhs);

		typedef struct		s_bestNode
		{
			int				pos;
			int				value;
		}					t_bestNode;

		void				setInitialDepth(int depth);

		bool				hashComp(const Board *a, const Board *b);

		int					minimax(Board *node, int depth, bool player);
		int					minimaxAB(Board *node, int depth, int A, int B, bool player);
		int					negamax(Board *node, int depth, int A, int B, int player);
		t_bestNode			negamaxID(Board *node, int pos, int depth, int A, int B, int player);
		int					ID(Board *node, int depth);

		int					nb_state = 0;

		void				resetTimer(void);
		void				startTimer();
		void				addTime(long long &dur);
		TIMEP				getTime();
		long long			getInt(TIMEP start, TIMEP end);
		void				printTime(long long dur, std::string str);
		void				showTime();

		int					getHistorySize();
		int					getTTSize();


	private:
		const std::vector<Board *>	_expandNode(Board *node, int player, int depth);
		void				_initBaseHashTable(void);
		void				_updateHistory(Board *node, int depth);
		uint64_t			_hashBoard(const Board *node) const;

		AbstractHeuristic	*_h;
		Board::Point		_player_color;
		int					_initial_depth;

		uint64_t			_baseHashTable[GRID_SIZE][2];
		std::unordered_map<uint64_t, int>	_historyTable;
		std::unordered_map<uint64_t, TTUtility::t_ttEntry>	_transpositionTable;


		long long			_t_expansion;
		long long			_t_eval;
		long long			_t_vector_clear;
		TIMEP				_timer;
		CheckForceMove		*_lineData;
		BrowseBoard			_browseBoard;

};

#endif
