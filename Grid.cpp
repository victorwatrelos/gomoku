#include "Grid.hpp"

Grid::Grid(void)
{
}

Grid::Grid( const Grid &obj )
{
	*this = obj;
}

Grid::~Grid(void)
{
}

bool		Grid::putStone(int x, int y)
{
	this->putStone(x + y * BORDER_SIZE);
	return true;
}

bool		Grid::putStone(int pos)
{
	(void)pos;
	return false;
}

const Grid::color	*Grid::getGrid(void) const
{
	return this->_grid;
}

Grid	&Grid::operator=(const Grid& obj)
{
	std::memcpy(this->_grid, obj.getGrid(), sizeof(this->_grid));
	return *this;
}

std::ostream	&operator<<(std::ostream &stream, const Grid &obj)
{
	stream << "obj: Grid" << std::endl;
	auto grid = obj.getGrid();
	for (auto i = 0u; i < Grid::TOT_SIZE; ++i)
	{
		if (!(i % Grid::BORDER_SIZE) && i > 0u)
		{
			std::cout << std::endl;
		}
		switch (grid[i])
		{
			case Grid::color::NONE:
				std::cout << ".";
				break;
			case Grid::color::WHITE:
			   std::cout << "o";
			   break;
			case Grid::color::BLACK:
			   std::cout << "x";
			   break;
		}
		std::cout << " ";
	}
	std::cout << std::endl;
	return stream;
}
