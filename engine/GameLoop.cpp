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
//	this->_players[1] = new STDINPlayer("White", Board::Point::WHITE);
	this->_players[1] = new AIPlayer("White", Board::Point::WHITE);
}

void		GameLoop::_initDisplay(void) {
	this->_display = new StdOutDisplay();
}

void		GameLoop::_getPlayerMove(AbstractPlayer &player) {
	int	pos;

	while (1)
	{
		pos = player.getMove(this->_board);
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
			this->_getPlayerMove(*p);
			this->_display->displayBoard(this->_board);
			if (this->_board.isWinningBoard())
			{
				terminated = true;
				return ;
			}
		}
	}
}
