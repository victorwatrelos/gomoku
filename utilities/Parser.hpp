#ifndef PARSER
# define PARSER

# include <string>
# include <iostream>

namespace	Parser {
	enum PlayerType {AI, HUMAN, NONE};
	PlayerType	getPlayer(int argc, char **argv, int playerNb);
}
#endif

