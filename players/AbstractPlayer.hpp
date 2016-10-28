#ifndef ABSTRACTPLAYER_HPP
# define ABSTRACTPLAYER_HPP

# include <string>
# include "../Board.hpp"
# include <sstream>

class AbstractPlayer
{
	public:
		AbstractPlayer(void);
		AbstractPlayer(const std::string &name, const Board::Point &color);
		AbstractPlayer(const AbstractPlayer &obj);
		AbstractPlayer &operator=(const AbstractPlayer &p);
		virtual ~AbstractPlayer(void);
		virtual int			getMove(const Board & board) = 0;
		virtual std::string	getInfo(void) const;
		const std::string	&getName(void) const;
		const Board::Point	&getColor(void) const;
		void				addTime(long long t);
		void				dispAverage(void) const;
		std::string			getAverage(void) const;
		std::string			getLastTime(void) const;
	protected:
		std::string		_name;
		Board::Point	_color;
	private:
		std::string		_getStrTime(long long) const;
		int				_totGetMove = 0;
		long long		_totTime = 0;
		std::vector<long long>	_times;
};

#endif
