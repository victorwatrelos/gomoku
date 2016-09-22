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
	std::cout << "-";
}

void			StdOutDisplay::displayBoard(const Board &board) const {
	auto	point = board.getBoard();
	int		pos = 0;

	for (auto i = point.begin(); i != point.end(); ++i) {
		this->_dispPoint(*i);
		pos++;
		if (!(pos % GRID_LENGTH))
			std::cout << std::endl;
	}
	std::cout << std::endl;
}
