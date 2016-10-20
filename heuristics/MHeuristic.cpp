#include "MHeuristic.hpp"

MHeuristic::MHeuristic(void) {

}

MHeuristic::MHeuristic(const MHeuristic &obj) {
	*this = obj;
}

MHeuristic::~MHeuristic(void) {

}

int						MHeuristic::eval(Board *b, Board::Point color)
{
	return this->browse(b, color);
}

MHeuristic    &MHeuristic::operator=(const MHeuristic &p) {
	(void)p;
	return *this;
}

