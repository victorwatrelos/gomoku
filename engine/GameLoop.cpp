#include "GameLoop.hpp"

GameLoop::GameLoop(void) {
	this->_initServer();
	this->_createPlayers();
	this->_initDisplay();

}

GameLoop::GameLoop(const GameLoop &obj) {
	*this = obj;
}

GameLoop::~GameLoop(void) {
	delete this->_players[0];
	delete this->_players[1];
	delete this->_display;
	delete this->_server;
}

GameLoop	&GameLoop::operator=(const GameLoop &p) {
	(void)p;
	return *this;
}

void		GameLoop::_createPlayers(void) {
	this->_players[0] = new NetworkPlayer("Black", Board::Point::BLACK, this->_server);
	this->_players[1] = new NetworkPlayer("White", Board::Point::WHITE, this->_server);
}

void		GameLoop::_initServer(void) {
	this->_server = new Server();
}

void		GameLoop::_initDisplay(void) {
	this->_display = new NetworkDisplay();
}

void		GameLoop::_getPlayerMove(AbstractPlayer &player) {
	int	pos;

	while (1)
	{
		pos = player.getMove();
		std::cout << "pos: " << pos << std::endl;
		if (this->_board.isMoveValid(pos, player.getColor()))
		{
			this->_board.setMove(pos, player.getColor());
			return ;
		}
		std::cout << "Move invalid" << std::endl;
	}
}

void		GameLoop::loop(void) {
	bool	terminated = false;

	while (!terminated)
	{
		for (auto p : this->_players)
		{
			(void)p;
			//this->_getPlayerMove(*p);
			this->_display->displayBoard(this->_board);
			terminated = true;
			if (this->_board.isWinningBoard())
			{
				terminated = true;
			}
		}
	}
}
