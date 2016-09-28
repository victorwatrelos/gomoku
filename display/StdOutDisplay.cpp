#include "StdOutDisplay.hpp"

StdOutDisplay::StdOutDisplay(void) {

}

StdOutDisplay::StdOutDisplay(const StdOutDisplay &obj) {
	*this = obj;
}

StdOutDisplay::~StdOutDisplay(void) {

}

StdOutDisplay	&StdOutDisplay::operator=(const StdOutDisplay &p) {
	(void)p;
	return *this;
}

void			StdOutDisplay::_dispPoint(Board::Point &p) const {
	switch (p) {
		case Board::Point::EMPTY : std::cout << "-";
		   break;
		case Board::Point::BLACK : std::cout << "x";
		   break;
		case Board::Point::WHITE : std::cout << "o";
		   break;
	}
	std::cout << " ";
}

void			StdOutDisplay::displayBoard(const Board &board) {
	auto	point = board.getBoard();
	int		pos = 0;
	int		a;

	std::cout << "   ";
	for (a = 1 ; a <= GRID_LENGTH ; a++)
	{
		if (a < 10)
			std::cout << a << " ";
		else
			std::cout << a;
	}
	std:: cout << std::endl << "1  ";
	for (auto i = point.begin(); i != point.end(); ++i) {
		this->_dispPoint(*i);
		pos++;
		if (!(pos % GRID_LENGTH))
		{
			std::cout << std::endl << pos / GRID_LENGTH + 1 << " ";
			if (pos / GRID_LENGTH < 9)
				std::cout << " ";
		}
	}
	std::cout << std::endl;
}
