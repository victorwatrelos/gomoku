#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <iostream>
# include <sstream>
# include "../Board.hpp"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "../exception/SocketException.hpp"
# include <csignal>
# include "../lib/json.hpp"

class Server
{
	public:
		Server(void);
		Server(const Server &obj);
		Server &operator=(const Server &p);
		virtual ~Server(void);
		int		getMove(Board::Point &color);
		int		getColor();
		void	sendBoard(const Board &board);
		void	sendWinner(const Board::Point &point);
		static void	signalHandler(int signal);
		static Server	*current;
	private:
		void	_wait();
		int		_getClientColor(const Board::Point &color);
		int		_listenFd;
		int		_connfd;
		void	_initServer();
		void	_getClient();
		nlohmann::json	_getMsg(size_t size = 0);
		void			_sendMsg(const char *str);

		int		_nbTry = 0;
		bool	_lostCo = true;
		std::vector<std::string>	*_splitString(std::string &str);
};

#endif

