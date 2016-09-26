#ifndef BOARD_HPP
# define BOARD_HPP

# include <vector>
# include <iostream>
# include "define.hpp"

# define PEMPTY						(Board::Point::EMPTY)

class								Board
{


	public:
		enum class Point : char {EMPTY, BLACK, WHITE};

									Board(void);
									Board(const Board &p);
		virtual						~Board(void);
		Board&						operator=(const Board &p);

		const std::vector<Point>&	getBoard(void) const;
		void						setMove(int pos, Board::Point color);
		bool						isMoveValid(int pos, Board::Point color) const;
		bool						isWinningBoard(void) const;
		int							getIndex(int i, int j) const;

	private:
		bool						_checkWinningLine(bool isRow) const;
		bool						_checkWinningDiag(bool down) const;
		bool						_checkWinningBackDiag(bool down) const;
		bool						_checkDoubleThree(int pos, Board::Point color) const;
		void						_resetThreeCheck(int **three, int *it, int *space) const;
		int							*_checkThreeLine(int pos, Board::Point color, bool isHoriz) const;
		int							*_checkThreeDiag(int pos, Board::Point color) const;
		int							*_checkThreeBackDiag(int pos, Board::Point color) const;
		bool						_checkMoveInCapture(int pos, Board::Point color) const;


		std::vector<Point>			_board;
};

#endif
