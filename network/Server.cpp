#include "Server.hpp"

Server	*Server::current = nullptr;

Server::Server(void) {
	this->_initServer();
	Server::current = this;
	std::signal(SIGPIPE, Server::signalHandler);
}

void	Server::signalHandler(int signal) {
	if (signal == SIGPIPE)
	{
		std::cout << "Reconnection" << std::endl;
	}
}

void	Server::_initServer() {
	struct sockaddr_in serv_addr; 

	char sendBuff[1025];

	this->_listenFd = socket(AF_INET, SOCK_STREAM, 0);
	int		enable = 1;
	if (setsockopt(this->_listenFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		std::cout << "Setsockopt fail: " << strerror(errno) << std::endl;
		exit(1);
	}
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff)); 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(4202); 

	if (bind(this->_listenFd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "Unable to bind connection: " << strerror(errno) << std::endl;
		exit(1);
	}

	if (listen(this->_listenFd, 10) < 0)
	{
		std::cout << "Unable to listen: " << strerror(errno) << std::endl;
		exit(1);
	}
	this->_getClient();
}

int		Server::_getClientColor(const Board::Point &color) {
	switch (color) {
		case (Board::Point::BLACK):
			return (0);
		case (Board::Point::WHITE):
			return (1);
		case (Board::Point::EMPTY):
			return (2);
	}
	return (2);
}

void			Server::_sendMsg(const char *str) {
	int		ret;

	size_t size = strlen(str);
	while (size > 0)
	{
		if ((ret = write(this->_connfd, str, size)) < 0)
		{
			this->_lostCo = true;
			throw new SocketException;
		}
		size -= ret;
		str += ret;
	}

}

std::vector<std::string>	*Server::_splitString(std::string &str) {
	std::vector<std::string> *strings = new std::vector<std::string>;
	std::istringstream f(str);
	std::string s;    
	while (getline(f, s, '-')) {
		strings->push_back(s);
	}
	return (strings);
}

void		Server::sendBoard(const Board &board) {
	auto rawBoard = board.getBoard();
	std::vector<int>	grid;
	nlohmann::json		msg_json;
	msg_json["type"] = "board";
	for (auto &k: rawBoard)
	{
		grid.push_back(this->_getClientColor(k));
	}
	msg_json["data"]["grid"] = grid;
	msg_json["data"]["blackStone"] = board.getBlackCapturedStone();
	msg_json["data"]["whiteStone"] = board.getWhiteCapturedStone();
	try {
		this->_sendMsg(msg_json.dump().c_str());
	} catch (SocketException *e) {
		std::cout << e->what() << std::endl;
		delete e;
		this->_wait();
		this->_getClient();
		this->sendBoard(board);
	}
	this->_nbTry = 0;
}

void		Server::sendFinalStats(AbstractPlayer **players)
{
	nlohmann::json	msg_json;
	AbstractPlayer	*p;
	std::string		color;

	msg_json["type"] = "final_stats";
	for (int i = 0; i < 2; i++)
	{
		 p = players[i];
		if (p->getColor() == Board::Point::BLACK)
			color = "black";
		else
			color = "white";
		msg_json["data"][color]["average_time"] = p->getAverage();
		msg_json["data"][color]["info"] = p->getInfo();
	}
	try {
		this->_sendMsg(msg_json.dump().c_str());
	} catch (SocketException *e) {
		std::cout << e->what() << std::endl;
		delete e;
		this->_wait();
		this->_getClient();
		this->sendFinalStats(players);
	}
	this->_nbTry = 0;
}

void		Server::_wait(void)
{
	if (this->_nbTry > 10)
	{
		std::cout << "Front is down, exiting" << std::endl;
		exit(1);
	}
	std::cout << "Unable to get response from network" << std::endl;
	sleep(2);
	this->_nbTry++;
}

void		Server::sendLoopState(const AbstractPlayer &player, int turnNb, const Board::Point &timeRelatedColor)
{
	int				clientColor = this->_getClientColor(timeRelatedColor);
	nlohmann::json	msg_json;

	msg_json["type"] = "loop_stat";
	msg_json["data"]["time"]["color"] = clientColor;
	msg_json["data"]["time"]["duration"] = player.getLastTime();
	msg_json["data"]["turn_nb"] = turnNb;

	try {
		this->_sendMsg(msg_json.dump().c_str());
	} catch (SocketException *e) {
		std::cout << e->what() << std::endl;
		delete e;
		this->_wait();
		this->_getClient();
		this->sendLoopState(player, turnNb, timeRelatedColor);
	}
}

void		Server::sendWinner(const Board::Point &color) {
	int		clientColor = this->_getClientColor(color);

	nlohmann::json msg_json;

	msg_json["type"] = "winner";
	msg_json["data"]["player"] = clientColor;

	try {
		this->_sendMsg(msg_json.dump().c_str());
	} catch (SocketException *e) {
		std::cout << e->what() << std::endl;
		delete e;
		this->_wait();
		this->_getClient();
		this->sendWinner(color);
	}
	this->_nbTry = 0;
}

int			Server::getMove(Board::Point &color)
{
	int		iColor = this->_getClientColor(color);
	nlohmann::json msg_json;
	nlohmann::json res_json;

	msg_json["type"] = "get_move";
	msg_json["data"] = iColor;

	try {
		this->_sendMsg(msg_json.dump().c_str());
		res_json = this->_getMsg();
	} catch (SocketException *e) {
		std::cout << e->what() << std::endl;
		delete e;
		this->_getClient();
		this->_wait();
		return this->getMove(color);
	}
	if (res_json["type"] == "move")
	{
		this->_nbTry = 0;
		return res_json["data"]["pos"];
	}
	this->_wait();
	return this->getMove(color);
}

nlohmann::json	Server::_getMsg(size_t) {
	char			*p_res;
	size_t			size = 1024;
	std::string		res = "";
	int				reTry = 0;

	p_res = new char[size + 1]();
	while (42)
	{
		bzero(p_res, sizeof(char) * (size + 1));
		if ((read(this->_connfd, p_res, size)) < 0)
		{
			this->_lostCo = true;
			throw new SocketException;
		}
		res += p_res;
		try {
			auto tmp = nlohmann::json::parse(res);
			this->_nbTry = 0;
			delete p_res;
			return tmp;
		} catch (std::invalid_argument e) {
			if (reTry > 100)
			{
				std::cerr << "Failure: " << e.what() << std::endl;
				delete p_res;
				exit(1);
			}
			reTry++;
		}
	}
}

void	Server::_getClient() {
	nlohmann::json	res;

	std::cout << "waiting for client connection" << std::endl;
	this->_connfd = accept(this->_listenFd, (struct sockaddr*)NULL, NULL);

	try {
		res = this->_getMsg();
	} catch (SocketException *e) {
		std::cout << e->what() << std::endl;
		delete e;
		this->_getClient();
	}
	if (res["ACCEPTCO"] == "OK")
	{
		this->_lostCo = false;
		std::cout << "Client successfully connect" << std::endl;
		this->_nbTry = 0;
		return ;
	}
	std::cout << "Bad confirmation from client" << std::endl;
	this->_wait();
	this->_getClient();
}

Server::Server(const Server &obj) {
	*this = obj;
}

Server::~Server(void) {
	std::cout << "Shutdown client connection" << std::endl;
	shutdown(this->_connfd, SHUT_RDWR);
	close(this->_connfd);
	close(this->_listenFd);
}

Server    &Server::operator=(const Server &p) {
	(void)p;
	return *this;
}

