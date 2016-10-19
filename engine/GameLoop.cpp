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
//	this->_players[0] = new NetworkPlayer("Black", Board::Point::BLACK, this->_server);
	this->_players[1] = new NetworkPlayer("White", Board::Point::WHITE, this->_server);
	this->_players[0] = new AIPlayer("Black", Board::Point::BLACK);
//	this->_players[1] = new AIPlayer("White", Board::Point::WHITE);
}

void		GameLoop::_initServer(void) {
	this->_server = new Server();
}

void		GameLoop::_initDisplay(void) {
	this->_display = new NetworkDisplay(this->_server);
}

void		GameLoop::_getPlayerMove(AbstractPlayer &player) {
	int	pos;

	while (1)
	{
		pos = player.getMove(this->_board);
		if (this->_board.isMoveValid(pos, player.getColor()))
		{
			this->_board.setMove(pos, player.getColor());
			this->_board.setLastMoves(pos);
			return ;
		}
		std::cout << "Move invalid" << std::endl;
	}
}

void			GameLoop::launchGame(void) {
	auto p = this->loop();

	std::cout << "Winner is: " << p->getName() << std::endl;
	this->_server->sendWinner(p->getColor());
}

void                printT(unsigned long int t)
{
	int             m, s, ms, us;

	m = (t / 60000000);
	s = (t / 1000000) % 60;
	ms = (t / 1000) % 1000;
	us = t % 1000;
	printf("Time taken for turn: %dm%ds%dms%dus\n\n", m, s, ms, us);
}

AbstractPlayer	*GameLoop::loop(void)
{
	std::chrono::high_resolution_clock::time_point		start, end;
	long long											dur;
	
	this->_display->displayBoard(this->_board);
	while (1)
	{
		for (auto p : this->_players)
		{
			start = std::chrono::high_resolution_clock::now();
			this->_getPlayerMove(*p);
			end = std::chrono::high_resolution_clock::now();
			dur = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
			printT(dur);
			this->_display->displayBoard(this->_board);
			if (this->_board.isWinningBoard())
			{
				return (p);
			}
		}
	}
}
