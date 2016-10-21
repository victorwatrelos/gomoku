#ifndef HASHUTILITIES_HPP
# define HASHUTILITIES_HPP

# include <sys/time.h>
# include <boost/cstdint.hpp>
# include <boost/random.hpp>
# include "../define.hpp"

namespace HashUtilities
{

	uint64_t			**initZorb();
	
	static uint64_t 	**baseHashTable = nullptr;
	uint64_t			getBaseHashTableEntry(int i, int j);


}

#endif
