#include "Exception.hpp"

Exception::Exception() : msg("Generic error")
{
}

Exception::Exception(const std::string& err) : msg(err)
{
}

std::string Exception::what()
{
	return msg;
}
