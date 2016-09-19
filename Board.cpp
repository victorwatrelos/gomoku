#include "Board.hpp"

Board::Board(void) : _board(GRID_SIZE, 0) {
}

Board::Board(const Board &obj) {
	*this = obj;
}

Board::~Board(void) {

}

Board    &Board::operator=(const Board &p) {
	this->_board = p->_board;
	return *this;
}
