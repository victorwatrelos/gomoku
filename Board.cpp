#include "Board.hpp"

Board::Board(void) : _board(GRID_SIZE, Board::Point::EMPTY)
{
	this->_last_moves[0] = -1;
	this->_last_moves[1] = -1;
}

Board::Board(const Board &obj)
{
	*this = obj;
}

Board::~Board(void)
{
}

Board    								&Board::operator=(const Board &p)
{
	this->_board = p.getBoard();
	this->_last_moves[0] = p.getLastMoves(0);
	this->_last_moves[1] = p.getLastMoves(1);
	return *this;
}

const std::vector<Board::Point>&		Board::getBoard(void) const
{
	return (const_cast<const std::vector<Board::Point>&>(this->_board));
}

int										Board::getLastMoves(int which) const
{
	if (which < 0 || which > 1)
		return (-1);
	return (this->_last_moves[which]);
}

void									Board::setLastMoves(int pos)
{
	this->_last_moves[0] = this->_last_moves[1];
	this->_last_moves[1] = pos;
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

void									Board::setMove(int pos, Board::Point color)
{
	if (pos < 0 || pos >= GRID_SIZE)
		return ;
	this->_board[pos] = color;
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
	//score += this->_checkStreakDiag(true, color);
	//score += this->_checkStreakBackDiag(true, color);
	//score += this->_checkStreakLine(false, color);
	//score += this->_checkStreakDiag(false, color);
	//score += this->_checkStreakBackDiag(false, color);
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

/*
std::vector<Board*>		Board::expand(Point color)
{
	std::vector<Board*>	st;
	std::unordered_set<int>		dups;
	int							set = 0;

//	std::cout << "start expansion" << std::endl;
//	showBoard(*this);
	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (this->_board[pos] != PEMPTY)
		{
			this->_expandPoint(st, color, pos, dups, 2);
			set++;
		}
	}
//	showExpand2(dups, *this);
//	std::cout << "expansion end" << std::endl;
	return st;
}
*/

std::vector<Board*>		Board::expand(Point color)
{
	std::vector<Board*>	st;
	std::unordered_set<int>		dups;
	int							set = 0;
	int							pos;

	for (int i = 0 ; i < 2 ; i++)
	{
		if ((pos = this->getLastMoves(i)) != -1)
		{
			this->_expandPoint(st, color, pos, dups, 2);//Change to aiplayer too
			set++;
		}
	}
	return st;
}

void				Board::_expandPoint(std::vector<Board *> &st, Board::Point color, int pos, std::unordered_set<int> &dups, int depth)
{
	int				i, j, index;
	int				m, n;
	Board			*new_board;

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
					new_board = new Board(*this);
					new_board->setMove(index, color);
					st.push_back(new_board);
					dups.insert(index);
				}
			}
		}
		i++;
	}
}
