#ifndef BROWSEBOARD_HPP
# define BROWSEBOARD_HPP

# include <cstring>
# include "../Board.hpp"
# include "AbstractLineData.hpp"
# include "LineData.hpp"

class					BrowseBoard
{
	public:
						BrowseBoard(void);
						BrowseBoard(AbstractLineData *lineData);
						BrowseBoard(const BrowseBoard & rhs);
		virtual			~BrowseBoard(void);
		BrowseBoard&	operator=(const BrowseBoard & rhs);

		int				browse(const Board &b, Board::Point color);
		static bool		coordValid(int x, int y);
	private:


		const std::vector<Board::Point>	*_b;
		AbstractLineData		*_lineData;
		Board::Point	_color;
		Board::Point	_oppColor;

		void			_getD1Lines(void);
		void			_getD2Lines(void);
		void			_browseDLine(int startX, int startY, const AbstractLineData::t_dir &dir);
		void			_getHLines(void);
		void			_getVLines(void);
		void			_getLines(void);
};

#endif
