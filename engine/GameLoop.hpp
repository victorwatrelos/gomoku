#ifndef GAMELOOP_HPP
# define GAMELOOP_HPP

# include "../players/AbstractPlayer.hpp"
# include "../players/STDINPlayer.hpp"
# include "../players/AIPlayer.hpp"
# include "../players/NetworkPlayer.hpp"
# include "../Board.hpp"
# include "../display/StdOutDisplay.hpp"
# include "../display/NetworkDisplay.hpp"
# include "../network/Server.hpp"
# include <chrono>
# include "../utilities/Parser.hpp"

class GameLoop
{
	public:
		GameLoop(void);
		GameLoop(Parser::PlayerType p1, Parser::PlayerType p2);
		GameLoop(const GameLoop &obj);
		GameLoop &operator=(const GameLoop &p);
		virtual ~GameLoop(void);
		AbstractPlayer	*loop(void);
		void			launchGame(void);
	private:
		AbstractPlayer	*_players[2];
		AbstractDisplay	*_display;
		Board			_board;
		Server			*_server;
		void			_createPlayers();
		void			_getPlayerMove(AbstractPlayer &player);
		void			_initDisplay(void);
		void			_initServer(void);
		Parser::PlayerType	_p1;
		Parser::PlayerType	_p2;
};

#endif
