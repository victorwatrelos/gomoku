#include "loadBoard.hpp"
# define MAGIC (0xFAF87)
#include "../display/StdOutDisplay.hpp"
#include "../heuristics/MHeuristic.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <fstream>

void		checkForceMove();
void		testAi();
void		testFreeThree();


typedef struct		s_test_struct {
	std::string		filename;
	std::string		desc = "";
	Board::Point	color;
	int				res;
	int				calcRes = 0;
	bool			success = false;
	bool			runned = false;
}					t_test_struct;

void				test_board(t_test_struct &t, bool disp)
{
	StdOutDisplay		d;
	MHeuristic			h;
	auto 				b = getBoard(t.filename);
	int					res;

	res = h.eval(b, t.color);
	t.success = res == t.res;
	t.runned = true;
	t.calcRes = res;

	if (!t.success || disp)
	{
		std::cout << "Trying " << t.desc << ":" << std::endl;
		if (!t.success)
			std::cout << "Failure" << std::endl;
		d.displayBoard(*b);
		std::cout << "Expected: " << t.res << " eval: " << res << std::endl;
	}
}

void		displaySuccess(const std::vector<t_test_struct> t)
{
	int		i = 0;
	while (t[i].res != MAGIC)
	{
		if (!t[i].runned)
			std::cout << "/";
		else if (t[i].success)
			std::cout << ".";
		else
			std::cout << "F";
		i++;
	}
	std::cout << std::endl;
}

void		displaySorted(std::vector<t_test_struct> t)
{
	StdOutDisplay		d;

	std::sort(t.begin(), t.end(), 
			    [](const t_test_struct & a, const t_test_struct & b) -> bool
				{ 
				    return a.calcRes > b.calcRes; 
				});
	for (auto f : t)
	{
		if (f.res == MAGIC)
			continue ;

		std::cout << "expected: " << f.res << " calculated: " << f.calcRes << std::endl;
		d.displayBoard(*getBoard(f.filename));
		std::cout << "------------------" << std::endl;
	}

}

static void	test_heuri(int n, bool disp_sorted)
{
	int	i = 0;
	std::vector<t_test_struct>		test({
		{"boards/test_h_line", "Test with 5 H stone", Board::Point::BLACK, 100060},
		{"boards/test_V_line", "Test with 5 V stone", Board::Point::BLACK, 100060},
		{"boards/test_d1_line", "Test with 5 DIAG1 stone", Board::Point::BLACK, 100060},
		{"boards/test_d2_line", "Test with 5 DIAG2 stone", Board::Point::BLACK, 100060},
		{"boards/test_4_stone", "Test with 4 DIAG2 stone", Board::Point::BLACK, 320},
		{"boards/test_4_stone_blocked", "Test with 4 DIAG2 stone blocked on each border", Board::Point::BLACK, 16},
		{"boards/test_4_stone_blocked_wall", "Test with 4 DIAG2 stone blocked on each border", Board::Point::BLACK, 24},
		{"boards/test_4_stone_with_hole", "Test with 4 DIAG2 stone with hole in the middle", Board::Point::BLACK, 300},
		{"boards/test_3_stone", "Test with 3 DIAG1 stone", Board::Point::BLACK, 116},
		{"boards/test_3_stone_one_blocked", "Test with 3 DIAG1 stone", Board::Point::BLACK, 88},
		{"boards/test_3_stone_two_blocked", "Test with 3 DIAG1 stone", Board::Point::BLACK, 4},
		{"boards/test_3_stone_with_hole", "Test with 3 DIAG1 stone", Board::Point::BLACK, 100},
		{"boards/test_2_stone", "Test with 2 H stone", Board::Point::BLACK, 40},
		{"boards/test_2_stone_space", "Test with 2 H stone with hole", Board::Point::BLACK, 24},
		{"boards/test_1_stone", "Test with 1 H stone", Board::Point::BLACK, 16},
		{"boards/toto", "TOTO", Board::Point::BLACK, 32},
		{"", "", Board::Point::EMPTY, MAGIC, false},
	});
	if (n >= 0)
	{
		std::cout << "HERE" << std::endl;
		test_board(test[n], true);
		return ;
	}
	while (test[i].res != MAGIC)
	{
		test_board(test[i], false);
		i++;
	}
	displaySuccess(test);
	if (disp_sorted)
		displaySorted(test);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << argv[0] << " [full|sorted|force_move|test_ai] [id_to_try]" << std::endl;
		return 1;
	}
	if (argc == 3)
		test_heuri(std::stoi(argv[2]), false);
	else if (strcmp(argv[1], "full") == 0)
		test_heuri(-1, false);
	else if (strcmp(argv[1], "sorted") == 0)
		test_heuri(-1, true);
	else if (strcmp(argv[1], "force_move") == 0)
		checkForceMove();
	else if (strcmp(argv[1], "test_ai") == 0)
		testAi();
	else if (strcmp(argv[1], "test_free_three") == 0)
		testFreeThree();
	return 0;
}
