#ifndef ABSTRACTDISPLAY_HPP
# define ABSTRACTDISPLAY_HPP

# include "../Board.hpp"

class AbstractDisplay
{
	public:
		AbstractDisplay(void);
		AbstractDisplay(const AbstractDisplay &obj);
		AbstractDisplay &operator=(const AbstractDisplay &p);
		virtual ~AbstractDisplay(void);
		virtual void	displayBoard(const Board &board) const = 0;
	private:
};
#endif
