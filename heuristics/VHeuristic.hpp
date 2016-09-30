#ifndef VHEURISTIC
# define VHEURISTIC

# include "AbstractHeuristic.hpp"
# include <strings.h>


class VHeuristic : public AbstractHeuristic
{
	typedef struct		s_lineData
	{
		int				cons;
		int				empty;
		bool			lastEmpty;
		int				totStone;
	}					t_lineData;
	public:
		VHeuristic(void);
		VHeuristic(const VHeuristic &obj);
		VHeuristic &operator=(const VHeuristic &p);
		virtual ~VHeuristic(void);
		int				eval(Board *b, const Board::Point &color, bool neg);
		bool			display = false;
	private:
		std::chrono::high_resolution_clock::time_point    _start;
		Board::Point	_color;
		int				_totPoints;

		void			_startTimer(void);
		void			_endTimer(void);
		void			_getLine(const std::vector<Board::Point> &b);
		void			_addPointForLine();
		void			_parsePointOfLine(const Board::Point &b);
		t_lineData		_lineData;
};
#endif

