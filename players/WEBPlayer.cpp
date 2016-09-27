#ifndef WEBPLAYER_HPP
# define WEBPLAYER_HPP

# include <iostream>
# include "../define.hpp"
# include "AbstractPlayer.hpp"

class WEBPlayer : public AbstractPlayer
{
	public:
		WEBPlayer(void);
		WEBPlayer(const std::string &name, const Board::Point &color);
		WEBPlayer(const WEBPlayer &obj);
		WEBPlayer &operator=(const WEBPlayer &p);
		virtual ~WEBPlayer(void);
		int			getMove(void);
	private:
		int			_getEntry(const std::string &str) const;
};

#endif
