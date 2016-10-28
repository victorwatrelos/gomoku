#include "testFreeThree.hpp"

void			print_validMove(Board *b)
{
	Board::Point		black = Board::Point::BLACK;
	Board::Point		white = Board::Point::WHITE;

	for (int pos = 0 ; pos < GRID_SIZE ; pos++)
	{
		if (pos && pos % GRID_LENGTH == 0)
			std::cout << std::endl;
		if (b->lookAt(pos) != PEMPTY)
		{
			if (b->lookAt(pos) == black)
				std::cout << "x ";
			else
				std::cout << "o ";
		}
		else
		{
			if (b->isMoveValid(pos, black) && b->isMoveValid(pos, white))
				std::cout << "_ ";
			else if (b->isMoveValid(pos, black))
				std::cout << "b ";
			else if (b->isMoveValid(pos, white))
				std::cout << "w ";
			else
				std::cout << "| ";
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void			runTestFreeThree(const std::string &str)
{
	Board		*b = getBoard(str);

	print_validMove(b);
}

void			testFreeThree()
{
	std::vector<std::string>	lst({
				"free_three_board_test/test_1",
				"free_three_board_test/test_2"
				});
	for (auto test : lst)
	{
		runTestFreeThree(test);
	}
}
