#include "../Board.hpp"
# define MAGIC (0xFAF87)
#include "../display/StdOutDisplay.hpp"
#include "../heuristics/MHeuristic.hpp"

#include <string>
#include <sstream>
#include <vector>
# include <fstream>

static Board::Point		getPointOfChar(char c)
{
	switch (c)
	{
		case 'X':
			return Board::Point::BLACK;
		case 'O':
			return Board::Point::WHITE;
	}
	return Board::Point::EMPTY;
}

static Board	*getBoard(const std::string &filename)
{
	std::string line;
	std::ifstream infile(filename) ;
	std::vector<Board::Point>		grid;

	if ( infile ) {
		while ( getline( infile , line ) ) {
			for (auto c : line)
			{
				if (c == 'X' || c == 'O' || c == '_')
					grid.push_back(getPointOfChar(c));
			}
		}
	}
	infile.close( ) ;
	if (grid.size() != GRID_SIZE)
	{
		std::cout << grid.size() << std::endl;
		std::cout << "Bad size of grid for file " << filename << std::endl;
		return nullptr;
	}
	return new Board(grid);
}

typedef struct		s_test_struct {
	std::string		filename;
	std::string		desc = "";
	Board::Point	color;
	int				res;
	bool			success = false;
	bool			runned = false;
}					t_test_struct;

void				test_board(t_test_struct &t)
{
	StdOutDisplay		d;
	MHeuristic			h;
	auto 				b = getBoard(t.filename);
	int					res;

	res = h.eval(b, t.color);
	t.success = res == t.res;
	t.runned = true;

	if (!t.success)
	{
		std::cout << "Trying " << t.desc << ":" << std::endl;
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
				    return a.res > b.res; 
				});
	for (auto f : t)
	{
		if (f.res == MAGIC)
			continue ;
		std::cout << f.res << ":" << std::endl;
		d.displayBoard(*getBoard(f.filename));
		std::cout << "------------------" << std::endl;
	}

}

int main(int argc, char **argv)
{
	int					i = 0;
	std::vector<t_test_struct>		test({
		{"boards/test_h_line", "Test with 5 H stone", Board::Point::BLACK, 100060},
		{"boards/test_V_line", "Test with 5 V stone", Board::Point::BLACK, 100060},
		{"boards/test_d1_line", "Test with 5 DIAG1 stone", Board::Point::BLACK, 100060},
		{"boards/test_d2_line", "Test with 5 DIAG2 stone", Board::Point::BLACK, 100060},
		{"boards/test_4_stone", "Test with 4 DIAG2 stone", Board::Point::BLACK, 320},
		{"boards/test_4_stone_blocked", "Test with 4 DIAG2 stone blocked on each border", Board::Point::BLACK, 16},
		{"boards/test_4_stone_blocked_wall", "Test with 4 DIAG2 stone blocked on each border", Board::Point::BLACK, 24},
		{"boards/test_4_stone_with_hole", "Test with 4 DIAG2 stone with hole in the middle", Board::Point::BLACK, 304},
		{"boards/test_3_stone", "Test with 3 DIAG1 stone", Board::Point::BLACK, 116},
		{"boards/test_3_stone_one_blocked", "Test with 3 DIAG1 stone", Board::Point::BLACK, 88},
		{"boards/test_3_stone_two_blocked", "Test with 3 DIAG1 stone", Board::Point::BLACK, 4},
		{"boards/test_3_stone_with_hole", "Test with 3 DIAG1 stone", Board::Point::BLACK, 104},
		{"boards/test_2_stone", "Test with 2 H stone", Board::Point::BLACK, 40},
		{"boards/test_2_stone_space", "Test with 2 H stone with hole", Board::Point::BLACK, 24},
		{"boards/test_1_stone", "Test with 1 H stone", Board::Point::BLACK, 16},
		{"boards/toto", "TOTO", Board::Point::BLACK, 16},
		{"", "", Board::Point::EMPTY, MAGIC, false},
	});
	if (argc > 1)
	{
		i = std::stoi(argv[1]);
		test_board(test[i]);
	}
	else
	{
		while (test[i].res != MAGIC)
		{
			test_board(test[i]);
			i++;
		}
	}
	displaySuccess(test);
//	displaySorted(test);
	return 0;
}
