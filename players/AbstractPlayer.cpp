#include "AbstractPlayer.hpp"

AbstractPlayer::AbstractPlayer(void) {

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
