#ifndef NETWORKDISPLAY
# define NETWORKDISPLAY

# include "AbstractDisplay.hpp"
# include "../network/Server.hpp"

class NetworkDisplay : public AbstractDisplay
{
	public:
		NetworkDisplay(void);
		NetworkDisplay(const NetworkDisplay &obj);
		NetworkDisplay &operator=(const NetworkDisplay &p);
		virtual ~NetworkDisplay(void);
		void	displayBoard(const Board &board);
	private:
		Server	*_server;
};
#endif
