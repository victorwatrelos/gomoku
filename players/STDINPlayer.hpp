#ifndef STDINPLAYER
# define STDINPLAYER

# include <iostream>
# include "../define.hpp"
# include "AbstractPlayer.hpp"

class STDINPlayer : public AbstractPlayer
{
	public:
		STDINPlayer(void);
		STDINPlayer(const STDINPlayer &obj);
		STDINPlayer &operator=(const STDINPlayer &p);
		virtual ~STDINPlayer(void);
		int			getMove(void);
	private:
		int			_getEntry(const std::string &str) const;
};

#endif
