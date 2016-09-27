#ifndef GAMELOOP_HPP
# define GAMELOOP_HPP

# include "../players/AbstractPlayer.hpp"
# include "../players/STDINPlayer.hpp"
# include "../players/NetworkPlayer.hpp"
# include "../Board.hpp"
# include "../display/StdOutDisplay.hpp"
# include "../display/NetworkDisplay.hpp"
# include "../network/Server.hpp"

class GameLoop
{
	public:
		GameLoop(void);
		GameLoop(const GameLoop &obj);
		GameLoop &operator=(const GameLoop &p);
		virtual ~GameLoop(void);
		void	loop(void);
	private:
		AbstractPlayer	*_players[2];
		AbstractDisplay	*_display;
		Board			_board;
		Server			*_server;
		void			_createPlayers();
		void			_getPlayerMove(AbstractPlayer &player);
		void			_initDisplay(void);
		void			_initServer(void);
};

#endif
