#include "STDINPlayer.hpp"

STDINPlayer::STDINPlayer(void) {
}

STDINPlayer::STDINPlayer(const std::string &name, const Board::Point &color) 
{	
	this->_name = name;
	this->_color = color;
}

STDINPlayer::STDINPlayer(const STDINPlayer &obj) {
	*this = obj;
}

STDINPlayer::~STDINPlayer(void) {

}

int		STDINPlayer::_getEntry(const std::string &str) const {
	bool	coordOk = false;
	int		in;

	do {
		std::cout << str;
		std::cin >> in;
		if (std::cin && in > 0 && in <= GRID_LENGTH)
		{
			in--;
			coordOk = true;
		} else {
			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(4096,'\n');
			}
			std::cout << "Out of range" << std::endl;
		}
	} while (!coordOk);
	return in;
}

int		STDINPlayer::getMove(void) {
	int		x, y;

	x = this->_getEntry("Enter your x coord choice (1 - " + std::to_string(GRID_LENGTH) + "): ");
	y = this->_getEntry("Enter your y coord choice (1 - " + std::to_string(GRID_LENGTH) + "): ");
	return x + y * GRID_LENGTH;
}

STDINPlayer	&STDINPlayer::operator=(const STDINPlayer &p) {
	(void)p;
	return *this;
}
