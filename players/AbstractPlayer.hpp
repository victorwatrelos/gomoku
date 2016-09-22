#ifndef ABSTRACTPLAYER_HPP
# define ABSTRACTPLAYER_HPP

# include <string>

class AbstractPlayer
{
	public:
		AbstractPlayer(void);
		AbstractPlayer(const std::string &name);
		AbstractPlayer(const AbstractPlayer &obj);
		AbstractPlayer &operator=(const AbstractPlayer &p);
		virtual ~AbstractPlayer(void);
		virtual int			getMove() = 0;
		const std::string	&getName(void) const;
	protected:
		std::string		_name;
};

#endif
