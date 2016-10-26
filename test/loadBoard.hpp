#ifndef LOADBOARD
# define LOADBOARD

#include "../Board.hpp"
#include <string>
#include <sstream>
#include <vector>
# include <fstream>

Board	*getBoard(const std::string &filename);

#endif

