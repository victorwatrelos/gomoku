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
			int				nbCons = 0;
			Board::Point	color;
		}					t_lineData;

		typedef struct		s_dir {
			int x;
			int	y;
		}					t_dir;	

		enum class LineType : char {HORI, VERT, DIAG1, DIAG2};

		LineType		_currentLine;
		const std::vector<Board::Point>	*_b;
		int				_totScore = 0;
		t_lineData		_lineData;
		Board::Point	_color;
		Board::Point	_oppColor;

		bool			_coordValid(int x, int y);
		void			_getD1Lines(void);
		void			_getD2Lines(void);
		void			_browseDLine(int startX, int startY, const t_dir &dir);
		void			_reset(void);
		void			_resetLineData(void);
		void			_getHLines(void);
		void			_getVLines(void);
		void			_getLines(void);
		void			_analysePoint(const Board::Point &p);
};

#endif
