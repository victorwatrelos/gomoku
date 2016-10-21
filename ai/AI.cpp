#include "AI.hpp"

AI::AI(void)
{
	this->_h = nullptr;
	this->_player_color = PEMPTY;
}

AI::AI(const AI & rhs)
{
	*this = rhs;
}

AI::AI(AbstractHeuristic *h, Board::Point &color) : _h(h), _player_color(color)
{
	this->_initBaseHashTable();
}

AI::~AI(void)
{
}

AI&			AI::operator=(const AI & rhs)
{
	this->_h = rhs._h;
	this->_player_color = rhs._player_color;
	return *this;
}

void			AI::setInitialDepth(int depth)
{
	this->_initial_depth = depth;
}

void		AI::_initBaseHashTable()
{
	struct timeval									tv;
	gettimeofday(&tv, NULL);
	boost::mt19937									randGen(tv.tv_usec);
	boost::uniform_int<uint64_t>					uInt64Dist(0, std::numeric_limits<uint64_t>::max());
	boost::variate_generator<boost::mt19937&, boost::uniform_int<uint64_t> >	getRand(randGen, uInt64Dist);

	for (int i = 0 ; i < GRID_SIZE; i++)
	{
		for (int j = 0 ; j < 2 ; j++)
		{
			this->_baseHashTable[i][j] = getRand();
		}
	}
}

uint64_t		AI::_hashBoard(Board *node) const
{
	int			j;
	Board::Point	p;
	uint64_t	h = 0;

	for (int i = 0 ; i < GRID_SIZE ; i++)
	{
		if ((p = node->lookAt(i)) != Board::Point::EMPTY)
		{
			j = ((p == Board::Point::BLACK) ? 0 : 1);
			h = h ^ this->_baseHashTable[i][j];
		}
	}
	return (h);
}

void			AI::_updateHistory(Board *node, int depth)
{
	uint64_t	hash = this->_hashBoard(node);

	if (this->_historyTable.find(hash) == this->_historyTable.end())
		this->_historyTable[hash] = 0;
	this->_historyTable[hash] = this->_historyTable[hash] + depth * depth;
}

bool			AI::hashComp(Board *a, Board*b)
{   
	auto ita = this->_historyTable.find(this->_hashBoard(a));
	auto itb = this->_historyTable.find(this->_hashBoard(b));
	if (ita != this->_historyTable.end() && itb != this->_historyTable.end())
		return (ita->second > itb->second);
	else if (ita != this->_historyTable.end())
		return (false);
	return (true);
}   

/*
 * 		MINIMAX
 */

int			AI::minimax(Board *node, int depth, bool player)
{
	int		val, bestValue = 0;
	std::vector<Board*>	children;

	if (depth == 0)
		return (this->_h->eval(node, this->_player_color));

	if (player)
	{
		bestValue = -1000000;
		children = node->expand(this->_player_color);
		this->nb_state += children.size();
		for (auto child : children) {
			val = this->minimax(child, depth - 1, false);
			if (val > bestValue)
				bestValue = val;
		}
		for (auto &i : children)
			delete i;
		children.clear();
	}
	else
	{
		bestValue = 1000000;
		children = node->expand(Board::getOppColor(this->_player_color));
		this->nb_state += children.size();
		for (auto child : children) {
			val = this->minimax(child, depth - 1, true);
			if (val < bestValue)
				bestValue = val;
		}
		for (auto &i : children)
			delete i;
		children.clear();
	}
	return (bestValue);
}

int			AI::minimaxAB(Board *node, int depth, int A, int B, bool player)
{
	int		val, bestValue = 0;
	std::vector<Board*>	children;

	if (depth == 0)
		return (this->_h->eval(node, this->_player_color));

	if (player)
	{
		bestValue = -1000000;
		children = node->expand(this->_player_color);
		this->nb_state += children.size();
		for (auto child : children) {
			val = this->minimaxAB(child, depth - 1, A, B, false);
			if (val > bestValue)
				bestValue = val;
			if (bestValue > A)
				A = bestValue;
			if (B <= A)
				break;
		}
		for (auto &i : children)
			delete i;
		children.clear();
	}
	else
	{
		bestValue = 1000000;
		children = node->expand(Board::getOppColor(this->_player_color));
		this->nb_state += children.size();
		for (auto child : children) {
			val = this->minimaxAB(child, depth - 1, A, B, true);
			if (val < bestValue)
				bestValue = val;
			if (bestValue < B)
				B = bestValue;
			if (B <= A)
				break;
		}
		for (auto &i : children)
			delete i;
		children.clear();
	}
	return (bestValue);
}

int				AI::negamax(Board *node, int depth, int A, int B, int player)
{
	int		val, bestValue = 0;
	int		eval;
	std::vector<Board*>	children;

	if (depth == 0)
	{
		this->startTimer();
		eval = this->_h->eval(node, this->_player_color) * player;
		this->addTime(this->_t_eval);
		this->_updateHistory(node, depth);
		return (eval);
	}

	this->startTimer();

	if (player == 1)
		children = node->expand(this->_player_color);
	else
		children = node->expand(Board::getOppColor(this->_player_color));

//	std::sort(children.begin(), children.end(), *this);// with operator()

	std::sort(children.begin(), children.end(), [this](Board *a, Board *b) {return hashComp(a, b); });
	this->addTime(this->_t_expansion);
	this->nb_state += children.size();

	bestValue = -1000000;
	for (auto child : children) {
		val = -1 * this->negamax(child, depth - 1, -1 * B, -1 * A, -1 * player);
		if (val > bestValue)
			bestValue = val;
		if (val > A)
			A = val;
		if (A >= B)
		{
			this->_updateHistory(node, depth);
			break;
		}
	}

	this->startTimer();
	for (auto &i : children)
		delete i;
	children.clear();
	this->addTime(this->_t_vector_clear);
	return (bestValue);
}

void		AI::resetTimer()
{
	this->_t_expansion = 0;
	this->_t_eval = 0;
	this->_t_vector_clear = 0;
}

void		AI::startTimer()
{
	this->_timer = getTime();
}

void		AI::addTime(long long &dur)
{
	TIMEP	end;

	end = getTime();
	dur += getInt(this->_timer, end);
}

TIMEP		AI::getTime()
{
	return std::chrono::high_resolution_clock::now();
}

long long	AI::getInt(TIMEP start, TIMEP end)
{
	return std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
}

void		AI::printTime(long long t, std::string str)
{
	int             m, s, ms, us;

	m = (t / 60000000);
	s = (t / 1000000) % 60;
	ms = (t / 1000) % 1000;
	us = t % 1000;
	printf("%s: %dm%ds%dms%dus\n", str.c_str(), m, s, ms, us);
}

void		AI::showTime()
{
	long long 	tot = this->_t_expansion + this->_t_eval + this->_t_vector_clear;
	float		pc;

	this->printTime(this->_t_expansion, "expansion");
	pc = this->_t_expansion * 1.0f / tot;
	std::cout << (pc * 100) << "%" << std::endl;
	this->printTime(this->_t_eval, "eval");
	pc = this->_t_eval * 1.0f / tot;
	std::cout << (pc * 100) << "%" << std::endl;
	this->printTime(this->_t_vector_clear, "vector_clear");
	pc = this->_t_vector_clear * 1.0f / tot;
	std::cout << (pc * 100) << "%" << std::endl;
}
