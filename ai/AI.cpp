#include "AI.hpp"

AI::AI(void)
	: _lineData(new CheckForceMove()), _browseBoard(this->_lineData)
{
	this->_h = nullptr;
	this->_player_color = PEMPTY;
}

AI::AI(const AI & rhs)
{
	*this = rhs;
}

AI::AI(AbstractHeuristic *h, Board::Point &color)
	: _h(h), _player_color(color), _lineData(new CheckForceMove()), _browseBoard(this->_lineData)
{
	this->_historyTable.reserve(1'000'000);
	this->_transpositionTable.reserve(1'000'000);
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

void			AI::_updateHistory(Board &node, int depth)
{
	uint64_t	hash = node.getHash();

	if (this->_historyTable.find(hash) == this->_historyTable.end())
		this->_historyTable[hash] = 0;
//	this->_historyTable[hash] = this->_historyTable[hash] + std::pow(this->_initial_depth - depth, 2);
	this->_historyTable[hash] = this->_historyTable[hash] + std::pow(depth, 2);
}

/*
bool			AI::hashComp(const Board &a, const Board &b)
{
	auto ita = this->_historyTable.find(a.getHash());
	auto itb = this->_historyTable.find(b.getHash());

	if (ita != this->_historyTable.end() && itb != this->_historyTable.end())
		return (ita->second > itb->second);
	else if (ita != this->_historyTable.end())
		return (true);
	return (false);
}
*/

bool			AI::hashComp(const Board &a, const Board &b)
{
	auto ita = this->_historyTable.find(a.getHash());
	auto itb = this->_historyTable.find(b.getHash());
	auto itTTa = this->_transpositionTable.find(a.getHash());
	auto itTTb = this->_transpositionTable.find(b.getHash());

	if (ita != this->_historyTable.end() && itb != this->_historyTable.end())
		return (ita->second > itb->second);
	else if (ita != this->_historyTable.end())
		return (true);
	else if (itTTa != this->_transpositionTable.end() && itTTb != this->_transpositionTable.end())
		return ((itTTa->second).flag > (itTTb->second).flag);
	else if (itTTa != this->_transpositionTable.end())
		return (true);

	return (false);
}

int				AI::getHistorySize()
{
	return this->_historyTable.size();
}

int				AI::getTTSize()
{
	return this->_transpositionTable.size();
}

const std::vector<Board>		AI::_expandNode(Board &node, int player, int depth)
{
	std::unordered_set<int>		dups;
	std::vector<Board>		lstBoard;
	std::vector<Board>		tmpLstBoard;
	Board						*tmpBoard;

	
//	this->_browseBoard.browse(*node, this->_player_color);
//	if ((dups = this->_lineData->getForcedMove()).size() > 0)
//	{
//		for (auto i : dups)
//		{
//			tmpBoard = new Board(*node);
//			if (player > 0)
//				tmpBoard->setMove(i, this->_player_color);
//			else
//				tmpBoard->setMove(i, Board::getOppColor(this->_player_color));
//			lstBoard.push_back(tmpBoard);
//		}
//	}
	
	if (player == 1)
		tmpLstBoard = node.expand(this->_player_color);
	else
		tmpLstBoard = node.expand(Board::getOppColor(this->_player_color));
	//lstBoard.insert(lstBoard.end(), tmpLstBoard.begin(), tmpLstBoard.end());
	return tmpLstBoard;
}

int				AI::negamax(Board &node, int depth, int A, int B, int player)
{
	int						val, bestValue = 0;
	int						eval;
	std::vector<Board>		children;
	TTUtility::t_ttEntry	entry;
	int						origA = A;
	bool					cutoff = false;

	auto it = this->_transpositionTable.find(node.getHash());
	if (it != this->_transpositionTable.end())
	{
		entry = it->second;
		if (entry.depth >= depth)
		{
			if (entry.flag == TTUtility::Flag::EXACT)
				return entry.value;
			else if (entry.flag == TTUtility::Flag::LOWERBOUND)
				A = std::max( A, entry.value);
			else if (entry.flag == TTUtility::Flag::UPPERBOUND)
				B = std::min( B, entry.value);
			if (A >= B)
				return entry.value;
		}
	}

	if (depth == 0)
	{
//		this->startTimer();
		eval = this->_h->eval(&node, this->_player_color) * player;
//		this->addTime(this->_t_eval);
		return (eval);
	}

	//this->startTimer();
	children = this->_expandNode(node, player, depth);
	//this->addTime(this->_t_expansion);
	std::sort(children.begin(), children.end(), [this](Board &a, Board &b) {return this->hashComp(a, b); });
	this->nb_state += children.size();

	bestValue = -1'000'000;
	for (auto child : children) {
		val = -1 * this->negamax(child, depth - 1, -1 * B, -1 * A, -1 * player);
		if (val > bestValue)
			bestValue = val;
		if (val > A)
			A = val;
		if (A >= B)
		{
			this->_updateHistory(child, depth);
			cutoff = true;
			break;
		}
	}

	if (cutoff == false)
		this->_updateHistory(node, depth);

	entry.value = bestValue;
	entry.depth = depth;
	if (bestValue <= origA)
		entry.flag = TTUtility::Flag::UPPERBOUND;
	else if (bestValue >= B)
		entry.flag = TTUtility::Flag::LOWERBOUND;
	else
		entry.flag = TTUtility::Flag::EXACT;

	this->_transpositionTable[node.getHash()] = entry;

	//this->startTimer();
	children.clear();
	//this->addTime(this->_t_vector_clear);
	return (bestValue);
}
#include "../display/StdOutDisplay.hpp"

static void	merge(const std::vector<Board> &lst)
{
	std::vector<Board::Point> grid(GRID_SIZE, Board::Point::EMPTY);

	for (auto b : lst)
	{
		auto p = b.getBoard();
		for (int i = 0; i < GRID_SIZE; i++)
		{
			if (p[i] != Board::Point::EMPTY)
			{
				grid[i] = p[i];
			}
		}
	}
	StdOutDisplay	disp;
	disp.displayBoard(Board(grid));
}

int			AI::ID(const Board & board, Board::Point color)
{
	std::vector<Board>	children;
	int					best_h = -1'000'000;
	int					best_pos = 0;
	int					h_value;
	long long			maxTime = 100'000;
	long long			time = 0;
	TIMEP				start, end;
	int					d = 1;
	CheckForceMove		checkF;
	BrowseBoard			browse(&checkF);

	checkF.setBoards(&children);
	browse.browse(board, color);
	if (children.size() == 0)
		children = board.expand(color);
	merge(children);
	while (time < maxTime)
	{
		this->_initial_depth = d;
		start = std::chrono::high_resolution_clock::now();
		for (auto child : children)
		{
			h_value = -1 * this->negamax(child, d, -1'000'000, 1'000'000, -1);
			if (h_value > best_h)
			{
				best_h = h_value;
				best_pos = child.getLastMove();
			}
		}
		end = std::chrono::high_resolution_clock::now();
		time += this->getInt(start, end);
		d++;
	}
	std::cout << "Depth attained : " << d + 1 << std::endl;
	return best_pos;
}

/*
 * TIMER HELPER
 */

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
