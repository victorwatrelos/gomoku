#ifndef GRID_HPP
# define GRID_HPP

# include <iostream>
# include <string.h>


class Grid
{
	public:
		enum class color: char { NONE, WHITE, BLACK };
		static const unsigned int	BORDER_SIZE = 19;
		static const unsigned int	TOT_SIZE = BORDER_SIZE * BORDER_SIZE;

		Grid( void );
		Grid( const Grid &obj );
		virtual ~Grid();
		Grid		&operator=(const Grid& obj);
		friend		std::ostream	&operator<<(std::ostream& stream, const Grid &obj);
		bool		putStone(int x, int y);
		bool		putStone(int pos);
		bool		isValid( void ) const;
		const color	*getGrid( void ) const;
	private:
		color		_grid[TOT_SIZE] = {color::NONE};
};

#endif
