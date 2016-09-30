#ifndef VHEURISTIC
# define VHEURISTIC

# include "AbstractHeuristic.hpp"
# include <strings.h>


class VHeuristic : public AbstractHeuristic
{
	public:
	typedef struct		s_lineData
	{
		int				cons;
		int				totCons;
		int				empty;
		bool			lastEmpty;
		int				totStone;
	}					t_lineData;
		VHeuristic(void);
		VHeuristic(const VHeuristic &obj);
		VHeuristic &operator=(const VHeuristic &p);
		virtual ~VHeuristic(void);
		int				eval(Board *b, const Board::Point &color, bool neg);
		bool			display = false;
	private:
		std::chrono::high_resolution_clock::time_point    _start;
		Board::Point	_color;
		Board::Point	_oppColor;
		int				_totPoints;
		t_lineData		_lineData;

		void			_startTimer(void);
		void			_endTimer(void);
		void			_getLine(const std::vector<Board::Point> &b);
		void			_addPointForLine(bool isLastEmpty);
		void			_parsePointOfLine(const Board::Point &b);
		bool			_checkHoriPos(const std::vector<Board::Point> &b, int pos);
};
#endif

