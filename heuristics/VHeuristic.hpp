#ifndef VHEURISTIC
# define VHEURISTIC

# include "AbstractHeuristic.hpp"
#include <numeric> 
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
			bool			has4;
		}					t_lineData;
		typedef struct		s_dir
		{
			int				x;
			int				y;
		}					t_dir;
		VHeuristic(void);
		VHeuristic(const VHeuristic &obj);
		VHeuristic &operator=(const VHeuristic &p);
		void		displayTime(void);
		virtual ~VHeuristic(void);
		int				eval(Board *b, const Board::Point &color, int depth);
		bool			display = false;
	private:
		enum class LineType : char {HORI, VERT, DIAG1, DIAG2};

		std::chrono::high_resolution_clock::time_point    _start;
		Board::Point	_color;
		Board::Point	_oppColor;
		int				_totPoints;
		t_lineData		_lineData;
		LineType		_currentLine;
		bool			_isWinning;
		int				_depth;
		const std::vector<Board::Point>	*_b;
		std::vector<long long int>	_time;

		void			_startTimer(void);
		void			_endTimer(void);
		void			_getLine();
		void			_getVLine();
		void			_getHLine();
		void			_getD1Line();
		void			_getD2Line();
		bool			_coordValid(int x, int y);
		void			_browseDLine(int startX, int startY, const t_dir &dir);
		void			_addPointForLine(bool isLastEmpty);
		void			_parsePointOfLine(const Board::Point &b, int i);
		bool			_checkHoriPos(const std::vector<Board::Point> &b, int pos);
		bool			_checkVertPos(const std::vector<Board::Point> &b, int pos);
		bool			_checkDiagPos(const std::vector<Board::Point> &b, int pos, int step);
		bool			_checkFreeMove(int pos);
		int				_getTotPoints();
		static const int	STEP_DIAG1 = GRID_LENGTH + 1;
		static const int	STEP_DIAG2 = GRID_LENGTH - 1;
};
#endif

