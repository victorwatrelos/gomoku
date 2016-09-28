#include "NetworkDisplay.hpp"

NetworkDisplay::NetworkDisplay(Server *server) {
	this->_server = server;
}

NetworkDisplay::NetworkDisplay(const NetworkDisplay &obj) {
	*this = obj;
}

NetworkDisplay::~NetworkDisplay(void) {

}

void	NetworkDisplay::displayBoard(const Board &board) {
	this->_server->sendBoard(board);
}

NetworkDisplay    &NetworkDisplay::operator=(const NetworkDisplay &p) {
	(void)p;
	return *this;
}

