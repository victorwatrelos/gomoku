#include "../Board.hpp"
# define MAGIC (0xFAF87)
#include "../display/StdOutDisplay.hpp"
#include "../utilities/CheckForceMove.hpp"
#include "loadBoard.hpp"
# include "../utilities/BrowseBoard.hpp"

#include <string>
#include <sstream>
#include <vector>
# include <fstream>

typedef struct		s_check_force_move {
	std::string		filename;
}					t_check_force_move;

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

void	testOne(const t_check_force_move &data)
{
	CheckForceMove		lineData;
	BrowseBoard			browse(&lineData);
	std::vector<Board>	child;
	StdOutDisplay		disp;

	Board		*b = getBoard(data.filename);
	lineData.setBoards(&child);
	browse.browse(*b, Board::Point::BLACK);
	std::cout << "For board: " << std::endl;
	disp.displayBoard(*b);
	merge(child);
}

void	checkForceMove()
{
	std::vector<t_check_force_move>		lst({
			{"force_move_boards/test_1"},
			{"force_move_boards/test_2"}
			});
	for (auto d : lst)
	{
		testOne(d);
	}
}
