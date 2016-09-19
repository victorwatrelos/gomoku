#ifndef ABSTRACTPLAYER
# define ABSTRACTPLAYER

class AbstractPlayer
{
	public:
		AbstractPlayer(void);
		AbstractPlayer(const AbstractPlayer &obj);
		AbstractPlayer &operator=(const AbstractPlayer &p);
		virtual int	getMove() = 0;
		virtual ~AbstractPlayer(void);
	private:
};

#endif
