#include "Board.hpp"

Board::Board(void) : _board(GRID_SIZE, Board::Point::EMPTY), _lastMoves(3), _hash(0)
{
}

Board::Board(const std::vector<Point> &grid) : _board(grid), _lastMoves(3)
{
	this->_hashBoard();
}

Board::Board(const Board &obj)
{
	*this = obj;
}

Board    								&Board::operator=(const Board &p)
{
	this->_board = p.getBoard();
	this->_lastMoves = p.getLastMoves();
	this->_lastMove = p.getLastMove();
	this->_hash = p.getHash();
	this->_blackStoneCaptured = p.getBlackCapturedStone();
	this->_whiteStoneCaptured = p.getWhiteCapturedStone();
	return *this;
}

const std::vector<Board::Point>&		Board::getBoard(void) const
{
	return (const_cast<const std::vector<Board::Point>&>(this->_board));
}

uint64_t								Board::getHash() const
{
	return (this->_hash);
}

boost::circular_buffer<int>				Board::getLastMoves() const
{
	return (this->_lastMoves);
}

void									Board::setLastMoves(int pos)
{
	this->_lastMoves.push_back(pos);
	this->_lastMove = pos;
}

int										Board::getLastMove() const
{
//	return this->_lastMoves.back();
	return this->_lastMove;
}

bool									Board::isFirstMove() const
{
	if (this->_lastMoves.empty())
		return true;
	return false;
}

Board::Point							Board::lookAt(int index) const
{
	return (this->_board[index]);
}

Board::Point							Board::getOppColor(Point player_color)
{
	if (player_color == Point::WHITE)
		return Point::BLACK;
	return Point::WHITE;
}

void									Board::_addNCheckCapture(int &tmpPos, int n)
{
	if (tmpPos < 0)
		return;
	tmpPos += n;
	if (tmpPos >= GRID_SIZE)
		tmpPos = -1;
	//std::cout << "tmppos: " << tmpPos << "(" << tmpPos % GRID_LENGTH << "," << tmpPos / GRID_LENGTH << ")" << std::endl;
}

void									Board::_updatePosCheckCapture(int *tmpPos)
{
	this->_addNCheckCapture(tmpPos[DirIndex::HRIGHT], 1);
	if (tmpPos[DirIndex::HRIGHT] % GRID_LENGTH == 0)
	{
		tmpPos[DirIndex::HRIGHT] = -1;
	}
	this->_addNCheckCapture(tmpPos[DirIndex::HLEFT], -1);
	if (tmpPos[DirIndex::HLEFT] % GRID_LENGTH == (GRID_LENGTH - 1))
	{
		tmpPos[DirIndex::HLEFT] = -1;
	}
	this->_addNCheckCapture(tmpPos[DirIndex::VUP], -GRID_LENGTH);
	this->_addNCheckCapture(tmpPos[DirIndex::VDOWN], GRID_LENGTH);
	this->_addNCheckCapture(tmpPos[DirIndex::DIAG1UP], -(GRID_LENGTH + 1));
	this->_addNCheckCapture(tmpPos[DirIndex::DIAG1DOWN], GRID_LENGTH + 1);
	this->_addNCheckCapture(tmpPos[DirIndex::DIAG2UP], -(GRID_LENGTH - 1));
	this->_addNCheckCapture(tmpPos[DirIndex::DIAG2DOWN], (GRID_LENGTH - 1));
}

void									Board::_processPosCheckCapture(int *tmpPos, int *tmpAccrued, const Point &oppColor)
{
	for (int i = 0; i < 8; i++)
	{
		if (tmpPos[i] < 0)
			continue ;
		if (this->_board[tmpPos[i]] == oppColor)
			tmpAccrued[i]++;
	}
}

void									Board::_initTmpPosCheckCapture(int *tmpPos, int pos)
{
	for (int i = 0; i < 8; i++)
	{
		tmpPos[i] = pos;
	}
}

void									Board::_checkLastStoneCheckCapture(int *tmpPos, int *tmpAccrued, bool *toDelete, const Point &color)
{
	for (int i = 0; i < 8; i++)
	{
		if (tmpAccrued[i] != 2)
			continue ;
		if (this->_board[tmpPos[i]] == color)
			toDelete[i] = true;
	}
}

void									Board::_deletePosCheckCapture(int *tmpPos, bool *toDelete, const Board::Point &colorCurrentStone)
{
	for (int i = 0; i < 8; i++)
	{
		if (toDelete[i])
		{
			this->_board[tmpPos[i]] = Board::Point::EMPTY;
			this->_addMoveToHash(tmpPos[i], colorCurrentStone);
			if (colorCurrentStone == Board::Point::WHITE)
				this->_whiteStoneCaptured++;
			else
				this->_blackStoneCaptured++;
		}
	}
}

void									Board::_checkCapture(int pos, const Board::Point &color)
{
	int			tmpPos[8];
	int			tmpAccrued[8] = {};
	bool		toDelete[8] = {};
	const Point	oppColor = Board::getOppColor(color);

	bzero(toDelete, sizeof(bool) * 8);
	this->_initTmpPosCheckCapture(tmpPos, pos);
	for (int i = 0; i < 2; i++)
	{

		this->_updatePosCheckCapture(tmpPos);
		this->_processPosCheckCapture(tmpPos, tmpAccrued, oppColor);
	}
	this->_updatePosCheckCapture(tmpPos);
	this->_checkLastStoneCheckCapture(tmpPos, tmpAccrued, toDelete, color);
	this->_initTmpPosCheckCapture(tmpPos, pos);
	for (int i = 0; i < 2; i++)
	{
		this->_updatePosCheckCapture(tmpPos);
		this->_deletePosCheckCapture(tmpPos, toDelete, oppColor);
	}
}

int										Board::getWhiteCapturedStone(void) const
{
	return this->_whiteStoneCaptured;
}

int										Board::getBlackCapturedStone(void) const
{
	return this->_blackStoneCaptured;
}
void									Board::setMove(int pos, Board::Point color)
{
	if (pos < 0 || pos >= GRID_SIZE)
		return ;
	this->_board[pos] = color;
	this->_addMoveToHash(pos, color);
	this->setLastMoves(pos);
	this->_checkCapture(pos, color);
}

bool									Board::isMoveValid(int pos, Board::Point color) const
{
	if (pos < 0 || pos >= GRID_SIZE)
	{
//		std::cout << ((color == Board::Point::WHITE) ? "W " : "B ") << "pos: " << pos << " is out of bound" << std::endl;
		return (false);
	}
	else if (this->_board[pos] != Board::Point::EMPTY)
	{
//		std::cout << ((color == Board::Point::WHITE) ? "W " : "B ") << "pos: " << pos << " is already occupied" << std::endl;
		return (false);
	}
	else if (this->_checkMoveInCapture(pos, color))
	{
//		std::cout << ((color == Board::Point::WHITE) ? "W " : "B ") << "pos: " << pos << " is in capture" << std::endl;
		return (false);
	}
	else if (this->_checkDoubleThree(pos, color))
	{
//		std::cout << ((color == Board::Point::WHITE) ? "W " : "B ") << "pos: " << pos << " is in double free three" << std::endl;
		return (false);
	}
	return (true);
}

bool									Board::isWinningBoard(void) const
{
	if (this->_checkWinningLine(true))
		return (true);
	if (this->_checkWinningLine(false))
		return (true);
	if (this->_checkWinningDiag(true))
		return (true);
	if (this->_checkWinningDiag(false))
		return (true);
	if (this->_checkWinningBackDiag(true))
		return (true);
	if (this->_checkWinningBackDiag(false))
		return (true);
	if (this->_blackStoneCaptured >= 10)
	{
		std::cout << "Black stone are all captured" << std::endl;
		return (true);
	}
	if (this->_whiteStoneCaptured >= 10)
	{
		std::cout << "White stone are all captured" << std::endl;
		return (true);
	}
	return (false);
}

int							Board::getIndex(int i, int j) const
{
	int						index;
	index = j * GRID_LENGTH + i;
	if (index < 0)
		index = 0;
	else if (index >= GRID_SIZE)
		index = GRID_SIZE - 1;
	return (index);
}

void						Board::_addMoveToHash(int index, Board::Point color)
{
	int col = ((color == Board::Point::BLACK) ? 0 : 1);
	this->_hash = this->_hash ^ HashUtilities::getBaseHashTableEntry(index, col);
}

/*
 *		CHECK FOR WINNING BOARD FUNCTIONS
 */

int							Board::_getStreak(Board::Point last, Board::Point curr, int streak) const
{
	if (curr == Board::Point::EMPTY || curr != last)
		return (0);
	else if (curr == last)
		return (streak + 1);
	return (streak);
}

bool						Board::_checkWinningLine(bool isRow) const
{
	int						i, j, index;
	int						streak;
	Board::Point			curr, last;

	i = 0;
	last = Board::Point::EMPTY;
	while (i < GRID_LENGTH)
	{
		j = 0;
		streak = 0;
		while (j < GRID_LENGTH)
		{
			if (isRow)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];
			if ((streak = this->_getStreak(last, curr, streak)) == 4)
				return (true);
			last = curr;
			j++;
		}
		i++;
	}
	return (false);
}

bool						Board::_checkWinningBackDiag(bool down) const
{
	int						a, i, j, index;
	int						streak;
	Board::Point			curr, last;

	a = 0;
	if (down)
		a++;
	while (a < GRID_LENGTH - 1)
	{
		i = a;
		j = 0;
		streak = 0;
		last = Board::Point::EMPTY;
		while (i < GRID_LENGTH)
		{
			if (down)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];
			if ((streak = this->_getStreak(last, curr, streak)) == 4)
				return (true);
			last = curr;
			i++;
			j++;
		}
		a++;
	}
	return (false);
}

bool						Board::_checkWinningDiag(bool down) const
{
	int						a, i, j, mod, index;
	int						streak = 0;
	Board::Point			curr, last;

	a = GRID_LENGTH - 1;
	while (a > 0)
	{
		i = a;
		j = 0;
		if (down) {
			mod = (GRID_LENGTH - 1 - a);
			j += mod;
			i += mod;
		}
		streak = 0;
		last = Board::Point::EMPTY;
		while (i > 0 && j < GRID_LENGTH)
		{
			index = this->getIndex(i, j);
			curr = this->_board[index];
			if ((streak = this->_getStreak(last, curr, streak)) == 4)
				return (true);
			last = curr;
			i--;
			j++;
		}
		a--;
	}
	return (false);
}

/*
 *		CHECK FOR DOUBLE THREE FUNCTIONS
 */

bool					Board::_checkDoubleThree(int pos, Board::Point color) const
{
	int					*three;

	if ((three = this->_checkThreeLine(pos, color, false)) != nullptr)
	{
		for (int i = 0 ; i < 3 ; i++) {
			if (three[i] == pos)
				continue ;
			if ((this->_checkThreeLine(three[i], color, true)) != nullptr)
				return (true);
			if ((this->_checkThreeBackDiag(three[i], color)) != nullptr)
				return (true);
			if ((this->_checkThreeDiag(three[i], color)) != nullptr)
				return (true);
		}
	}
	if ((three = this->_checkThreeLine(pos, color, true)) != nullptr)
	{
		for (int i = 0 ; i < 3 ; i++) {
			if (three[i] == pos)
				continue ;
			if ((this->_checkThreeLine(three[i], color, false)) != nullptr)
				return (true);
			if ((this->_checkThreeBackDiag(three[i], color)) != nullptr)
				return (true);
			if ((this->_checkThreeDiag(three[i], color)) != nullptr)
				return (true);
		}
	}
	if ((three = this->_checkThreeDiag(pos, color)) != nullptr)
	{
		for (int i = 0 ; i < 3 ; i++) {
			if (three[i] == pos)
				continue ;
			if ((this->_checkThreeLine(three[i], color, true)) != nullptr)
				return (true);
			if ((this->_checkThreeLine(three[i], color, false)) != nullptr)
				return (true);
			if ((this->_checkThreeBackDiag(three[i], color)) != nullptr)
				return (true);
		}
	}
	if ((three = this->_checkThreeBackDiag(pos, color)) != nullptr)
	{
		for (int i = 0 ; i < 3 ; i++) {
			if (three[i] == pos)
				continue ;
			if ((this->_checkThreeLine(three[i], color, true)) != nullptr)
				return (true);
			if ((this->_checkThreeLine(three[i], color, false)) != nullptr)
				return (true);
			if ((this->_checkThreeDiag(three[i], color)) != nullptr)
				return (true);
		}
	}
	return (false);
}

void					Board::_resetThreeCheck(int **three, int *it, int *space) const
{
	(*three)[0] = 0;
	(*three)[1] = 0;
	(*three)[2] = 0;
	*it = 0;
	*space = 0;
}

int						*Board::_checkThreeLine(int pos, Board::Point color, bool isHoriz) const
{
	int					*three = new int[3];
	int					it = 0;
	int					space = 0;
	int					i, j, index;
	int					stop;
	Board::Point		curr, last;

	if (isHoriz)
	{
		i = pos / GRID_LENGTH;
		j = pos % GRID_LENGTH - 3;
		stop = (pos % GRID_LENGTH) + 5;
	}
	else
	{
		i = pos % GRID_LENGTH;
		j = pos / GRID_LENGTH - 3;
		stop = (pos / GRID_LENGTH) + 5;
	}
	if (j < -2)
		return nullptr;
	else if (j <= 0)
		j = 1;
	if (stop >= GRID_LENGTH)
		stop = GRID_LENGTH;
	index = this->getIndex(i, j - 1);
	last = this->_board[index];
	while (j < stop)
	{
		if (isHoriz)
			index = this->getIndex(j, i);
		else
			index = this->getIndex(i, j);
		if (index != pos)
			curr = this->_board[index];
		else
			curr = color;
		if (it == 3 && curr == PEMPTY)
			return three;
		else if (last == color && curr == PEMPTY && space < 2)
			space++;
		else if (((last == PEMPTY && curr == color) || (last == color && curr == color)) && space < 2)
		{
			if (it < 3)
				three[it++] = index;
			else
				this->_resetThreeCheck(&three, &it, &space);
		}
		else if ((last == PEMPTY && curr == PEMPTY) || (curr != last))
			this->_resetThreeCheck(&three, &it, &space);
		last = curr;
		j++;
	}
	return nullptr;
}

int						*Board::_checkThreeBackDiag(int pos, Board::Point color) const
{
	int					*three = new int[3];
	int					it = 0;
	int					space = 0;
	int					i, j, index;
	int					stopI, stopJ;
	Board::Point		curr, last;

	i = pos % GRID_LENGTH + 3;
	j = pos / GRID_LENGTH - 3;
	stopI = pos % GRID_LENGTH - 5;
	stopJ = (pos / GRID_LENGTH) + 5;
	if (j < -2 || i > GRID_LENGTH + 1)
		return nullptr;
	if (j <= 0)
		j = 1;
	if (i > GRID_LENGTH - 2)
		i = GRID_LENGTH - 2;
	if (stopI < 0)
		stopI = 0;
	if (stopJ >= GRID_LENGTH)
		stopJ = GRID_LENGTH;
	index = this->getIndex(i - 1, j - 1);
	last = this->_board[index];
	while (i >= stopI && j < stopJ)
	{
		index = this->getIndex(i, j);
		if (index != pos)
			curr = this->_board[index];
		else
			curr = color;
		if (it == 3 && curr == PEMPTY)
			return three;
		else if (last == color && curr == PEMPTY && space < 2)
			space++;
		else if (((last == PEMPTY && curr == color) || (last == color && curr == color)) && space < 2)
		{
			if (it < 3)
				three[it++] = index;
			else
				this->_resetThreeCheck(&three, &it, &space);
		}
		else if ((last == PEMPTY && curr == PEMPTY) || (curr != last))
			this->_resetThreeCheck(&three, &it, &space);
		last = curr;
		i--;
		j++;
	}
	return nullptr;
}

int						*Board::_checkThreeDiag(int pos, Board::Point color) const
{
	int					*three = new int[3];
	int					it = 0;
	int					space = 0;
	int					i, j, index;
	int					stopI, stopJ;
	Board::Point		curr, last;

	i = pos % GRID_LENGTH - 3;
	j = pos / GRID_LENGTH - 3;
	stopI = (pos % GRID_LENGTH) + 5;
	stopJ = (pos / GRID_LENGTH) + 5;
	if (j < -2 || i < -2)
		return nullptr;
	if (j <= 0)
		j = 1;
	if (i <= 0)
		i = 1;
	if (stopI >= GRID_LENGTH)
		stopI = GRID_LENGTH;
	if (stopJ >= GRID_LENGTH)
		stopJ = GRID_LENGTH;
	index = this->getIndex(i - 1, j - 1);
	last = this->_board[index];
	while (i < stopI && j < stopJ)
	{
		index = this->getIndex(i, j);
		if (index != pos)
			curr = this->_board[index];
		else
			curr = color;
		if (it == 3 && curr == PEMPTY)
			return three;
		else if (last == color && curr == PEMPTY && space < 2)
			space++;
		else if (((last == PEMPTY && curr == color) || (last == color && curr == color)) && space < 2)
		{
			if (it < 3)
				three[it++] = index;
			else
				this->_resetThreeCheck(&three, &it, &space);
		}
		else if ((last == PEMPTY && curr == PEMPTY) || (curr != last))
			this->_resetThreeCheck(&three, &it, &space);
		last = curr;
		i++;
		j++;
	}
	return nullptr;
}

/*
 *			CHECK FOR MOVE IN CAPTURE
 */

bool					Board::_checkCapture(Board::Point color, Board::Point opp, int i, int j, int modI, int modJ) const
{
	int					index1, index2, index3;

	index1 = this->getIndex(i - 1 * modI, j - 1 * modJ);
	index2 = this->getIndex(i + 1 * modI, j + 1 * modJ);
	index3 = this->getIndex(i + 2 * modI, j + 2 * modJ);
	if (this->_board[index1] == opp && this->_board[index2] == color && this->_board[index3] == opp)
		return (true);
	index1 = this->getIndex(i - 2 * modI, j - 2 * modJ);
	index2 = this->getIndex(i - 1 * modI, j - 1 * modJ);
	index3 = this->getIndex(i + 1 * modI, j + 1 * modJ);
	if (this->_board[index1] == opp && this->_board[index2] == color && this->_board[index3] == opp)
		return (true);
	return (false);
}

bool					Board::_checkMoveInCapture(int pos, Board::Point color) const
{
	int					i, j;
	Board::Point		opp;

	if (color == Board::Point::WHITE)
		opp = Board::Point::BLACK;
	else
		opp = Board::Point::WHITE;
	i = pos % GRID_LENGTH;
	j = pos / GRID_LENGTH;

	if (this->_checkCapture(color, opp, i, j, 1, 1))
		return (true);
	if (this->_checkCapture(color, opp, i, j, 1, -1))
		return (true);
	if (this->_checkCapture(color, opp, i, j, 1, 0))
		return (true);
	if (this->_checkCapture(color, opp, i, j, 0, -1))
		return (true);
	return (false);
}

/*
 * TEST
 */

# define 		POL(X, Y)  ((X == Y) ? 1 : -1)

int							Board::_checkStreakLine(bool isRow, Board::Point color) const
{
	int						i, j, index;
	int						streak;
	Board::Point			curr, last;
	int						score = 0;

	i = 0;
	last = Board::Point::EMPTY;
	while (i < GRID_LENGTH)
	{
		j = 0;
		streak = 0;
		while (j < GRID_LENGTH)
		{
			if (isRow)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];

			if (curr == Board::Point::EMPTY || curr != last)
			{
				//std::cout << "Pow: " << std::pow(4, streak) * POL(last, color) << " " << streak << " : " << score << std::endl;
				score += std::pow(4, streak) * POL(last, color);
				//std::cout << "score: " << score << std::endl;
				streak = 0;
			}
			else if (curr == last)
				streak++;
			if (streak == 4)
			{
				//std::cout << "HERE" << std::endl;
				score += std::pow(4, streak * 2) * POL(curr, color);
				streak = 0;
			}

			last = curr;
			j++;
		}
		i++;
	}
	if (streak != 0)
		score += std::pow(4, streak) * POL(curr, color);
	return (score);
}

int							Board::_checkStreakBackDiag(bool down, Board::Point color) const
{
	int						a, i, j, index;
	int						streak;
	Board::Point			curr, last;
	int						score = 0;

	last = Board::Point::EMPTY;
	a = 0;
	if (down)
		a++;
	while (a < GRID_LENGTH - 1)
	{
		i = a;
		j = 0;
		streak = 0;
		while (i < GRID_LENGTH)
		{
			if (down)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
			{
				score += std::pow(4, streak) * POL(last, color);
				streak = 0;
			}
			else if (curr == last)
				streak++;
			if (streak == 4)
			{
				score += std::pow(4, streak * 2) * POL(last, color);
				streak = 0;
			}
			last = curr;
			i++;
			j++;
		}
		a++;
	}
	if (streak != 0)
		score += std::pow(4, streak) * POL(last, color);
	return (score);
}

int							Board::_checkStreakDiag(bool down, Board::Point color) const
{
	int						a, i, j, index;
	int						streak = 0;
	Board::Point			curr, last;
	int						score = 0;

	last = Board::Point::EMPTY;
	a = GRID_LENGTH - 1;
	while (a > 0)
	{
		i = a;
		j = 0;
		if (down)
			j++;
		streak = 0;
		while (i > 0)
		{
			if (down)
				index = this->getIndex(j, i);
			else
				index = this->getIndex(i, j);
			curr = this->_board[index];
			if (curr == Board::Point::EMPTY || curr != last)
			{
				score += std::pow(4, streak) * POL(last, color);
				streak = 0;
			}
			else if (curr == last)
				streak++;
			if (streak == 4)
			{
				score += std::pow(4, streak * 2) * POL(last, color);
				streak = 0;
			}
			last = curr;
			i--;
			j++;
		}
		a--;
	}
	if (streak != 0)
		score += std::pow(4, streak) * POL(last, color);
	return (score);
}

int					Board::getScore(Board::Point color)
{
	int				score = 0;

	score += this->_checkStreakLine(true, color);
	score += this->_checkStreakDiag(true, color);
	score += this->_checkStreakBackDiag(true, color);
	score += this->_checkStreakLine(false, color);
	score += this->_checkStreakDiag(false, color);
	score += this->_checkStreakBackDiag(false, color);
	return score;
}

/*
 *			EXPAND FUNCTIONS
 */

void				showExpand2(std::unordered_set<int> dups, const Board &board)
{
	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (pos % GRID_LENGTH == 0)
			std::cout << std::endl;
		if (dups.find(pos) != dups.end())
		{
			if (board.lookAt(pos) != PEMPTY)
				std::cout << "X ";
			else
				std::cout << "O ";
		}
		else
		{
			if (board.lookAt(pos) == Board::Point::BLACK)
				std::cout << "B ";
			else if (board.lookAt(pos) == Board::Point::WHITE)
				std::cout << "W ";
			else
				std::cout << "_ ";
		}
	}
	std::cout << std::endl;
}

void				showBoard(const Board &board)
{
	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (pos % GRID_LENGTH == 0)
			std::cout << std::endl;
		if (board.lookAt(pos) == Board::Point::BLACK)
			std::cout << "B ";
		else if (board.lookAt(pos) == Board::Point::WHITE)
			std::cout << "W ";
		else
			std::cout << "_ ";
	}
	std::cout << std::endl;
}


std::vector<Board>		Board::expand(Point color) const
{
	std::vector<Board>	st;
	std::unordered_set<int>		dups;
	int							set = 0;

	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (this->_board[pos] != PEMPTY)
		{
			this->_expandPoint(st, color, pos, dups, 2);
			set++;
		}
	}
	if (set == 0)
	{
		st.push_back(*this);
		(st.back()).setMove(GRID_SIZE / 2, color);
	}
	return st;
}

/*
std::vector<Board>		Board::expand(Point color) const
{
	std::vector<Board>	st;
	std::unordered_set<int>		dups;
	int							set = 0;

	for (auto pos : this->_lastMoves)
	{
		this->_expandPoint(st, color, pos, dups, 2);
		set++;
	}
	if (set == 0)
	{
		st.push_back(*this);
		(st.back()).setMove(GRID_SIZE / 2, color);
	}
		
	//	this->_expandPoint(st, color, GRID_SIZE / 2, dups, 2);
//	showExpand2(dups, *this);
	if (st.empty())
		std::cout << "IS EMPTY!!!!!" << std::endl;
	return st;
}
*/

void				Board::_expandPoint(std::vector<Board> &st, Board::Point color, int pos, std::unordered_set<int> &dups, int depth) const
{
	int				i, j, index;
	int				m, n;

	i = pos % GRID_LENGTH - depth;
	j = pos / GRID_LENGTH - depth;
	m = pos % GRID_LENGTH + depth + 1;
	n = pos / GRID_LENGTH + depth + 1;
	
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	if (m > GRID_LENGTH)
		m = GRID_LENGTH;
	if (n > GRID_LENGTH)
		n = GRID_LENGTH;
	while (i < m)
	{
		for (int jj = j ; jj < n ; jj++)
		{
			index = this->getIndex(i, jj);
			if (dups.find(index) == dups.end())
			{
				if (this->isMoveValid(index, color))
				{
					st.push_back(*this);
					(st.back()).setMove(index, color);
					dups.insert(index);
				}
			}
		}
		i++;
	}
}

void		Board::_hashBoard()
{
	int			j;
	Board::Point	p;
	this->_hash = 0;

	for (int i = 0 ; i < GRID_SIZE ; i++)
	{
		if ((p = this->_board[i]) != Board::Point::EMPTY)
		{
			j = ((p == Board::Point::BLACK) ? 0 : 1);
			this->_hash = this->_hash ^ HashUtilities::getBaseHashTableEntry(i, j);
		}
	}
}
