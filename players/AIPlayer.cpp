#include "AIPlayer.hpp"

AIPlayer::AIPlayer(void) {
	this->_name = "AIPlayer";
	this->_color = PEMPTY;
}

AIPlayer::AIPlayer(const AIPlayer & rhs)
{
	*this = rhs;
}

AIPlayer::AIPlayer(const std::string &name, const Board::Point &color)
{
	this->_name = name;
	this->_color = color;
	this->_h = new SimpleHeuristic();
	this->_ai = new AI(this->_h, this->_color);
}

AIPlayer::~AIPlayer(void) {}

AIPlayer&			AIPlayer::operator=(const AIPlayer & rhs)
{
	this->_name = rhs._name;
	this->_color = rhs._color;
	this->_h = rhs._h;
	this->_ai = rhs._ai;
	return *this;
}
/*
int					AIPlayer::getMove(const Board &board)
{
	Board				new_board;
	int					best_h = -1;
	int					best_pos = 0;
	int					h_value;

	this->_ai->nb_state = 0;
	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (board.isMoveValid(pos, this->_color))
		{
			new_board = board;
			new_board.setMove(pos, this->_color);
			h_value = this->_ai->minimax(&new_board, 1, true);
			if (h_value > best_h)
			{
				best_h = h_value;
				best_pos = pos;
			}
		}
	}
	std::cout << "nb state explored : " << this->_ai->nb_state << std::endl;
	return best_pos;
}
*/

void                printTTT(unsigned long int t, int a)
{
	int             m, s, ms, us;

	m = (t / 60000000);
	s = (t / 1000000) % 60;
	ms = (t / 1000) % 1000;
	us = t % 1000;
	if (a == 1)
		printf("Time taken for expansion: %dm%ds%dms%dus\n", m, s, ms, us);
	else if (a == 2)
		printf("Time taken for minmax iter: %dm%ds%dms%dus\n", m, s, ms, us);
}

void				AIPlayer::_expandPoints(Board::Point color, int pos, std::unordered_set<int> &dups, const Board &b, int depth)
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
			index = b.getIndex(i, jj);
			if (dups.find(index) == dups.end())
			{
				if (b.isMoveValid(index, color))
					dups.insert(index);
			}
		}
		i++;
	}
}

void				showExpand(std::unordered_set<int> dups, const Board &board)
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
			if (board.lookAt(pos) != PEMPTY)
				std::cout << "E ";
			else
				std::cout << "_ ";
		}
	}
	std::cout << std::endl;
}

int						AIPlayer::getMove(const Board &board)
{
	Board				new_board;
	int					best_h = -1;
	int					best_pos = 0;
	int					h_value;
	int					set = 0;
	std::unordered_set<int>		dups;
	std::vector<Board::Point>	b = board.getBoard();
	std::chrono::high_resolution_clock::time_point		start, end;
	long long											dur;

start = std::chrono::high_resolution_clock::now();
	this->_ai->nb_state = 0;
	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (b[pos] != PEMPTY)
		{
			this->_expandPoints(this->_color, pos, dups, board, 2);
			set++;
		}
	}
	if (set == 0)
		this->_expandPoints(this->_color, GRID_SIZE / 2, dups, board, 2);
end = std::chrono::high_resolution_clock::now();
dur = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
printTTT(dur, 1);

//	showExpand(dups, board);
start = std::chrono::high_resolution_clock::now();
	for (auto i : dups)
	{
		new_board = board;
		new_board.setMove(i, this->_color);
//		h_value = this->_ai->minimax(&new_board, 3, true);
		h_value = this->_ai->minimaxAB(&new_board, 3, -100000, 100000, true);
//		h_value = this->_ai->negamax(&new_board, 3, -100000, 100000, 1);
		if (h_value > best_h)
		{
			best_h = h_value;
			best_pos = i;
		}
	}
end = std::chrono::high_resolution_clock::now();
dur = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
printTTT(dur, 2);
	std::cout << "nb state explored : " << this->_ai->nb_state << std::endl;
	return best_pos;
}
