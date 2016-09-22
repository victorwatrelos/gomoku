#include "AbstractPlayer.hpp"

AbstractPlayer::AbstractPlayer(void) 
	: _name("default") {
}

AbstractPlayer::AbstractPlayer(const std::string &name) 
	: _name(name) {
}

AbstractPlayer::AbstractPlayer(const AbstractPlayer &obj) {
	*this = obj;
}

AbstractPlayer::~AbstractPlayer(void) {

}

AbstractPlayer	&AbstractPlayer::operator=(const AbstractPlayer &p) {
	(void)p;
	return *this;
}

const std::string	&AbstractPlayer::getName(void) const {
	return this->_name;
}
