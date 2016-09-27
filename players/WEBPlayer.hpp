#include "WEBPlayer.hpp"

WEBPlayer::WEBPlayer(void) {
}

WEBPlayer::WEBPlayer(const std::string &name, const Board::Point &color) 
{	
	this->_name = name;
	this->_color = color;
}

WEBPlayer::WEBPlayer(const WEBPlayer &obj) {
	*this = obj;
}

WEBPlayer::~WEBPlayer(void) {

}

int		WEBPlayer::getMove(void) {
}

WEBPlayer	&WEBPlayer::operator=(const WEBPlayer &p) {
	(void)p;
	return *this;
}
