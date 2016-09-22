#include "AbstractDisplay.hpp"

AbstractDisplay::AbstractDisplay(void) {

}

AbstractDisplay::AbstractDisplay(const AbstractDisplay &obj) {
	*this = obj;
}

AbstractDisplay::~AbstractDisplay(void) {

}

AbstractDisplay	&AbstractDisplay::operator=(const AbstractDisplay &p) {
	(void)p;
	return *this;
}
