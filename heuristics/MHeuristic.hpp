#ifndef MHEURISTIC_HPP
# define MHEURISTIC_HPP

# include "AbstractHeuristic.hpp"
# include <cstring>

class					MHeuristic : public AbstractHeuristic
{
	public:
						MHeuristic(void);
						MHeuristic(const MHeuristic & rhs);
		virtual			~MHeuristic(void);
		MHeuristic&	operator=(const MHeuristic & rhs);

		int				eval(Board *b, Board::Point color);
	private:
		typedef struct		s_lineData
		{
			int				nbCons;
		}					t_lineData;
		enum class LineType : char {HORI, VERT, DIAG1, DIAG2};

		LineType		_currentLine;
		const std::vector<Board::Point>	*_b;
		int				_totScore = 0;
		t_lineData		_lineData;
		Board::Point	_color;

		void			_reset(void);
		void			_resetLineData(void);
		void			_getHLines(void);
		void			_getLines(void);
		void			_analysePoint(const Board::Point &p);
};

#endif
