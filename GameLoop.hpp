#ifndef GAMELOOP_HPP
# define GAMELOOP_HPP


class					GameLoop
{
	public:
						GameLoop();
						GameLoop(const GameLoop & rhs);
		virtual			~GameLoop();

		GameLoop&		operator=(const GameLoop & rhs);

	private:
		Board			*board;
		AbstractPlayer	*player1;
		AbstractPlayer	*player2;
};



#endif
