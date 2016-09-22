#ifndef GAMELOOP_HPP
# define GAMELOOP_HPP

# include "../players/AbstractPlayer.hpp"
# include "../players/STDINPlayer.hpp"
# include "../Board.hpp"
# include "../display/StdOutDisplay.hpp"

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
		void			_createPlayers();
		void			_getPlayerMove(AbstractPlayer &player);
		void			_initDisplay(void);
};

#endif
