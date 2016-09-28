#include "State.hpp"

State::State(void) {}

State::State(const State & rhs)
{
	*this = rhs;
}

State::State(Board b, Board::Point player_col, AbstractHeuristic *h) : _board(b), _player_col(player_col), _h(h)
{
}

State::~State(void) {}

State&		State::operator=(const State & rhs)
{
	this->_board = rhs._board;
	this->_h = rhs._h;
	return *this;
}

int			State::eval()
{
	return (this->_h->eval(&this->_board));
}

/*
std::vector<State*>		State::expand(void)
{
	std::vector<State*>	st;
	Board				new_board;
	State				*new_state;

	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (this->_board.isMoveValid(pos, this->_player_col))
		{
			new_board = this->_board;
			new_board.setMove(pos, this->_player_col);
			new_state = new State(new_board, this->_player_col, this->_h);
			st.push_back(new_state);
		}
	}
	return st;
}
*/
std::vector<State*>		State::expand(void)
{
	std::vector<State*>	st;
	std::vector<Board::Point>	bobo = this->_board.getBoard();
	int							set = 0;

	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (bobo[pos] != PEMPTY)
		{
			this->_expandPoint(st, pos);
			set++;
		}
	}
	if (set == 0)
		this->_expandPoint(st, 180);
	return st;
}

void				State::_expandPoint(std::vector<State *>st, int pos)
{
	int				i, j;
	int				m, n;
	Board			new_board;
	State			*new_state;

	i = pos % GRID_LENGTH - 3;
	j = pos / GRID_LENGTH - 3;
	m = pos % GRID_LENGTH + 3;
	n = pos / GRID_LENGTH + 3;
	
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	if (m >= GRID_LENGTH)
		m = GRID_LENGTH - 1;
	if (n >= GRID_LENGTH)
		n = GRID_LENGTH - 1;
	for ( ; i < m ; i++ )
	{
		for ( ; j < n ; j++ )
		{
			new_board = this->_board;
			new_board.setMove(pos, this->_player_col);
			new_state = new State(new_board, this->_player_col, this->_h);
			st.push_back(new_state);
		}
	}

}


