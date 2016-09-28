#include "NetworkPlayer.hpp"

NetworkPlayer::NetworkPlayer(void) {

}

NetworkPlayer::NetworkPlayer(const std::string &name, const Board::Point &color, Server *server)
	: _server(server)
{
	this->_name = name;
	this->_color = color;
}

int		NetworkPlayer::getMove(const Board & board) {
	(void)board;
	return this->_server->getMove(this->_color);
}

NetworkPlayer::NetworkPlayer(const NetworkPlayer &obj) {
	*this = obj;
}

NetworkPlayer::~NetworkPlayer(void) {

}
