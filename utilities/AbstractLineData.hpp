#ifndef ABSTRACTLINEDATA
# define ABSTRACTLINEDATA

# include "../Board.hpp"
# include "BoardUtilities.hpp"

class				AbstractLineData
{
	public:
		enum class LineType : char {HORI, VERT, DIAG1, DIAG2};
		typedef struct		s_dir {
			int x;
			int	y;
		}					t_dir;
		AbstractLineData(void);
		AbstractLineData(const AbstractLineData &obj);
		AbstractLineData &operator=(const AbstractLineData &p);
		virtual ~AbstractLineData(void);
		virtual void			init(const Board::Point &color, const Board *b);
		virtual void			addPoint(const Board::Point &color, int pos);
		int				getScore(void);
		void			setDir(LineType dir);
		void			endOfLine(void);
	protected:
		int				_nbCons = 0;
		Board::Point	_currentColor;
		Board::Point	_playerColor;
		int				_tot = 0;
		LineType		_dir;
		int				_interSpace = 0;
		int				_posInter;
		int				_pos;
		bool			_lastIsSpace = false;
		bool			_startingSpace = false;
		bool			_endingSpace = false;
		const std::vector<Board::Point> *_grid;
		const Board		*_board;

		bool				_hasPlace(int pos);
		const t_dir			_getDir(void) const;
		virtual void		_endOfSeries(void) = 0;
		void				_display(void);
		static std::string	_getColor(const Board::Point &col);
		void				_addSpace(void);
		void				_addPointSameColor(void);
		void				_addPointOtherColor(const Board::Point &p, int pos);
};

#endif
