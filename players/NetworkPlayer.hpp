#ifndef NETWORKPLAYER
# define NETWORKPLAYER

# include "AbstractPlayer.hpp"
# include "../network/Server.hpp"

class NetworkPlayer : public AbstractPlayer
{
	public:
		NetworkPlayer(const std::string &name, const Board::Point &color, Server *server);
		NetworkPlayer(const NetworkPlayer &obj);
		virtual ~NetworkPlayer(void);
		int			getMove(const Board & board);
	private:
		NetworkPlayer(void);
		Server	*_server = nullptr;
};
#endif

