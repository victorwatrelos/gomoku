#ifndef SOCKETEXCEPTION
# define SOCKETEXCEPTION
class SocketException : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
		return "Socket disconnect";
	}
};
#endif

