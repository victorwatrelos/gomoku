#include "AbstractPlayer.hpp"

AbstractPlayer::AbstractPlayer(void) 
	: _name("default"), _color(Board::Point::BLACK) {
}

AbstractPlayer::AbstractPlayer(const std::string &name, const Board::Point &color) 
	: _name(name), _color(color) {
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

const Board::Point	&AbstractPlayer::getColor(void) const {

	return this->_color;

}
