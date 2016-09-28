#ifndef NETWORKDISPLAY
# define NETWORKDISPLAY

# include "AbstractDisplay.hpp"
# include "../network/Server.hpp"

class NetworkDisplay : public AbstractDisplay
{
	public:
		NetworkDisplay(Server *server);
		NetworkDisplay(const NetworkDisplay &obj);
		NetworkDisplay &operator=(const NetworkDisplay &p);
		virtual ~NetworkDisplay(void);
		void	displayBoard(const Board &board);
	private:
		NetworkDisplay(void);
		Server	*_server;
};
#endif
