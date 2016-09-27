#ifndef STDOUTDISPLAY_HPP
# define STDOUTDISPLAY_HPP

# include "AbstractDisplay.hpp"

class StdOutDisplay : public AbstractDisplay
{
	public:
		StdOutDisplay(void);
		StdOutDisplay(const StdOutDisplay &obj);
		StdOutDisplay &operator=(const StdOutDisplay &p);
		virtual ~StdOutDisplay(void);
		void	displayBoard(const Board &board);
	private:
		void	_dispPoint(Board::Point &p) const;
};

#endif
