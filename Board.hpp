#ifndef BOARD_HPP
# define BOARD_HPP


class				Board
{

	enum class Point : char {EMPTY, BLACK, WHITE};

	public:
								Board(void);
		virtual					~Board(void);
		Board&					operator=(const Board &p);

		std::vector<Point>		getBoard(void) const;
		bool					isMoveValid(int pos) const;
		bool					isWinningBoard(void) const;

	private:
		std::vector<Point>		_board;
};

#endif
