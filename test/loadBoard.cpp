#include "loadBoard.hpp"

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

Board	*getBoard(const std::string &filename)
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
