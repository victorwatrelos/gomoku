#ifndef STDINPLAYER
# define STDINPLAYER

# include <iostream>
# include "../define.hpp"
# include "AbstractPlayer.hpp"

class STDINPlayer : public AbstractPlayer
{
	public:
		STDINPlayer(void);
		STDINPlayer(const std::string &name, const Board::Point &color);
		STDINPlayer(const STDINPlayer &obj);
	//	STDINPlayer &operator=(const STDINPlayer &p);
		virtual ~STDINPlayer(void);
		int			getMove(const Board & board);
	private:
		int			_getEntry(const std::string &str) const;
};

#endif
