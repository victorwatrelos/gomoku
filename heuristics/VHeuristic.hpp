#ifndef VHEURISTIC
# define VHEURISTIC

# include "AbstractHeuristic.hpp"

class VHeuristic : public AbstractHeuristic
{
	public:
		VHeuristic(void);
		VHeuristic(const VHeuristic &obj);
		VHeuristic &operator=(const VHeuristic &p);
		virtual ~VHeuristic(void);
		int				eval(Board *b);
	private:
		std::chrono::high_resolution_clock::time_point    _start;

		void		_startTimer(void);
		void		_endTimer(void);
};
#endif

