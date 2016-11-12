#ifndef PARSER
# define PARSER

# include <string>
# include <iostream>

namespace	Parser {
	enum PlayerType {AI1, AI2, AI3, HUMAN, NONE};
	PlayerType	getPlayer(int argc, char **argv, int playerNb);
}
#endif

