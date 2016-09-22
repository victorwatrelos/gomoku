#ifndef ABSTRACTPLAYER_HPP
# define ABSTRACTPLAYER_HPP

# include <string>
# include "../Board.hpp"

class AbstractPlayer
{
	public:
		AbstractPlayer(void);
		AbstractPlayer(const std::string &name, const Board::Point &color);
		AbstractPlayer(const AbstractPlayer &obj);
		AbstractPlayer &operator=(const AbstractPlayer &p);
		virtual ~AbstractPlayer(void);
		virtual int			getMove() = 0;
		const std::string	&getName(void) const;
		const Board::Point	&getColor(void) const;
	protected:
		std::string		_name;
		Board::Point	_color;
};

#endif
