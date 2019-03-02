// Exception
// Wrapper class for exceptions

#ifndef Exception_HPP
#define Exception_HPP

#include <string>

class Exception 
{
private:
	std::string msg;

public:
	Exception();
	Exception(const std::string& err);

	// return exception's error message
	std::string what();
};

#endif