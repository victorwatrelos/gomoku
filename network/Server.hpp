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
	private:
		int		_getClientColor(const Board::Point &color);
		int		_listenFd;
		int		_connfd;
		void	_initServer();
		void	_getClient();
		std::string		*_getMsg(size_t size);
		void			_sendMsg(const char *str);
		const char	*ACCEPT_CO = "ACCEPTCO";
		bool	_lostCo = true;
		std::vector<std::string>	*_splitString(std::string &str);
};

#endif

