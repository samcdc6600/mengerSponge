#include <sstream>
#include "include/defs.hpp"


static constexpr char FILE_NAME [] { "defs.cpp" };


std::string error::genErrorLocationStr(const std::string & file, const std::string & func)
{
	std::stringstream ret {};
    ret<<"(in function \""<<func<<"\", in file \""<<file<<"\")";
	return ret.str();
}