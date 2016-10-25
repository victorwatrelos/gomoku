#include "Parser.hpp"

static Parser::PlayerType	getInfo(const std::string &arg, int pNb)
{
	std::string		player = "p" + std::to_string(pNb);
	std::size_t	pos;

	if (arg.length() < 3)
		return Parser::PlayerType::NONE;
	pos = arg.find(player);
	if (pos != 0)
		return Parser::PlayerType::NONE;
	if (arg.find("human", 2) != std::string::npos)
	{
		return Parser::PlayerType::HUMAN;
	}
	if (arg.find("ai", 2) != std::string::npos)
	{
		return Parser::PlayerType::AI;
	}
	return Parser::PlayerType::NONE;
}

Parser::PlayerType	Parser::getPlayer(int argc, char **argv, int playerNb)
{
	Parser::PlayerType	res;
	for (int i = 1; i < argc; i++)
	{
		if ((res = getInfo(argv[i], playerNb)) != Parser::PlayerType::NONE)
			return res;
	}
	return Parser::PlayerType::HUMAN;
}
