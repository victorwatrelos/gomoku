#include "GameLoop.hpp"

GameLoop::GameLoop(void) {
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
}

GameLoop	&GameLoop::operator=(const GameLoop &p) {
	(void)p;
	return *this;
}

void		GameLoop::_createPlayers(void) {
	this->_players[0] = new STDINPlayer("Black", Board::Point::BLACK);
	this->_players[1] = new STDINPlayer("White", Board::Point::WHITE);
}

void		GameLoop::_initDisplay(void) {
	this->_display = new StdOutDisplay();
}

void		GameLoop::_getPlayerMove(AbstractPlayer &player) {
	int	pos = player.getMove();

	while (1)
	{
		if (this->_board.isMoveValid(pos))
		{
			//TODO add stone to board
			return ;
		}
	}
}

void		GameLoop::loop(void) {
	bool	terminated = false;

	while (!terminated)
	{
		for (auto p : this->_players)
		{
			this->_getPlayerMove(*p);
			this->_display->displayBoard(this->_board);
			if (this->_board.isWinningBoard())
			{
				terminated = true;
			}
		}
	}
}
