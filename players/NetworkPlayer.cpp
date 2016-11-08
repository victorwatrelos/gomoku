#include "NetworkPlayer.hpp"

NetworkPlayer::NetworkPlayer(void) {

}

NetworkPlayer::NetworkPlayer(const std::string &name, const Board::Point &color, Server *server)
	: _server(server)
{
	this->_name = name;
	this->_color = color;
	this->_aiPlayer = new AIPlayer("Human concelor", color, 0);
}

int		NetworkPlayer::getMove(const Board & board) {
	int	pos = this->_aiPlayer->getMove(board);
	return this->_server->getMove(this->_color, pos);
}

NetworkPlayer::NetworkPlayer(const NetworkPlayer &obj) {
	*this = obj;
}

NetworkPlayer::~NetworkPlayer(void) {

}
