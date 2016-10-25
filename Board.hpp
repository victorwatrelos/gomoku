#ifndef BOARD_HPP
# define BOARD_HPP

# include <boost/circular_buffer.hpp>
# include <vector>
# include <unordered_set>
# include <iostream>
# include <cmath>
# include "define.hpp"
# include "utilities/HashUtilities.hpp"

# define PEMPTY						(Board::Point::EMPTY)

class								Board
{


	public:
		enum class Point : char {EMPTY, BLACK, WHITE};

									Board(void);
									Board(const Board &p);
									Board(const std::vector<Point> &grid);
		virtual						~Board(void);
		Board&						operator=(const Board &p);

		const std::vector<Point>&	getBoard(void) const;
		Board::Point				lookAt(int index) const;
		void						setMove(int pos, Board::Point color);
		bool						isMoveValid(int pos, Board::Point color) const;
		bool						isWinningBoard(void) const;
		int							getIndex(int i, int j) const;

		uint64_t					getHash() const;
		int							getScore(Board::Point color);

		std::vector<Board*>			expand(Point color);
		
		static Point				getOppColor(Point player_col);

		boost::circular_buffer<int>	getLastMoves() const;
		void						setLastMoves(int pos);
		int							getLastMove() const; 
		bool						isFirstMove() const;

	private:
		int							_getStreak(Board::Point last, Board::Point curr, int streak) const;
		bool						_checkWinningLine(bool isRow) const;
		bool						_checkWinningDiag(bool down) const;
		bool						_checkWinningBackDiag(bool down) const;
		bool						_checkDoubleThree(int pos, Board::Point color) const;
		void						_resetThreeCheck(int **three, int *it, int *space) const;
		int							*_checkThreeLine(int pos, Board::Point color, bool isHoriz) const;
		int							*_checkThreeDiag(int pos, Board::Point color) const;
		int							*_checkThreeBackDiag(int pos, Board::Point color) const;
		bool						_checkMoveInCapture(int pos, Board::Point color) const;
		bool						_checkCapture(Board::Point color, Board::Point opp, int i, int j, int modI, int modJ) const;


		int							_checkStreakLine(bool isRow, Board::Point color) const;
		int							_checkStreakDiag(bool down, Board::Point color) const;
		int							_checkStreakBackDiag(bool down, Board::Point color) const;

		void						_expandPoint(std::vector<Board *> &st, Board::Point color, int pos, std::unordered_set<int> &dups, int depth);

		void						_addMoveToHash(int index, Board::Point color);

		std::vector<Point>			_board;
		boost::circular_buffer<int>	_lastMoves;
		uint64_t					_hash;
		int							_lastMove;
};

#endif
