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

std::string			AbstractPlayer::getInfo(void) const
{
	return " ";
}
void				AbstractPlayer::addTime(long long t)
{
	this->_totTime += t;
	this->_times.push_back(t);
	this->_totGetMove++;
	std::cout << "Time for turn " << this->_totGetMove << " of " << this->_name << ":";
	std::cout << this->_getStrTime(t) << std::endl;
}

std::string			AbstractPlayer::getLastTime(void) const
{
	return this->_getStrTime(this->_times.back());
}

std::string		AbstractPlayer::_getStrTime(long long t) const
{
	int             m, s, ms, us;

	m = (t / 60000000);
	s = (t / 1000000) % 60;
	ms = (t / 1000) % 1000;
	us = t % 1000;
	std::ostringstream oss;
	oss << m << "m" << s << "s" << ms << "ms" << us << "us";
	return oss.str();
}

void				AbstractPlayer::dispAverage(void) const
{
	std::cout << "Average time for get move of player "
		<< this->_name << " in " << this->_totGetMove
		<< " turns:";
	std::cout << this->getAverage() << std::endl;
}

std::string			AbstractPlayer::getAverage(void) const
{
	long long		t = this->_totTime / this->_totGetMove;

	return this->_getStrTime(t);
}
