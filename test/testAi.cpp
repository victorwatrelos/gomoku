#include "testAi.hpp"

typedef struct	s_test_ai {
	std::string	filename;
}				t_test_ai;

void		testOneAi(const t_test_ai &t)
{
	Board	*b = getBoard(t.filename);
	AIPlayer	player("Black", Board::Point::BLACK);
	StdOutDisplay	disp;

	std::cout << "Base board: " << std::endl;
	disp.displayBoard(*b);
	int move = player.getMove(*b);
	b->setMove(move, Board::Point::WHITE);
	std::cout << "Play in " << move % GRID_LENGTH << " " << move / GRID_LENGTH << std::endl;
	disp.displayBoard(*b);
}

void		testAi()
{
	std::vector<t_test_ai>	lst({
			{"ai_board_test/test_1"}
			});
	for (auto a : lst)
	{
		testOneAi(a);
	}
}
