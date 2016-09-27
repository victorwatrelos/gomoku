#include "NetworkDisplay.hpp"

NetworkDisplay::NetworkDisplay(void) {

}

NetworkDisplay::NetworkDisplay(const NetworkDisplay &obj) {
	*this = obj;
}

NetworkDisplay::~NetworkDisplay(void) {

}

void	NetworkDisplay::displayBoard(const Board &board) {
	printf("p:   %p\n", this->_server);
	this->_server->sendBoard(board);
}

NetworkDisplay    &NetworkDisplay::operator=(const NetworkDisplay &p) {
	(void)p;
	return *this;
}

