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
	this->_name = p._name;
	this->_color = p._color;
	return *this;
}

const std::string	&AbstractPlayer::getName(void) const {
	return this->_name;
}

const Board::Point	&AbstractPlayer::getColor(void) const {

	return this->_color;

}

void				AbstractPlayer::addTime(long long t)
{
	this->_totTime += t;
	this->_totGetMove++;
	std::cout << "Time for turn " << this->_totGetMove << " of " << this->_name << ":";
	this->_dispTime(t);
	std::cout << std::endl;
}

void				AbstractPlayer::_dispTime(long long t)
{
	int             m, s, ms, us;

	m = (t / 60000000);
	s = (t / 1000000) % 60;
	ms = (t / 1000) % 1000;
	us = t % 1000;
	printf("%dm%ds%dms%dus",
			m, s, ms, us);
}

void				AbstractPlayer::dispAverage(void)
{
	long long		t = this->_totTime / this->_totGetMove;

	std::cout << "Average time for get move of player "
		<< this->_name << " in " << this->_totGetMove
		<< " turns:";
	this->_dispTime(t);
	std::cout << std::endl;
}
