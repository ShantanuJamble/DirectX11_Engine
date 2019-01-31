#include "ErrorHandler.h"


bool ErrorLogCall(const char * function, const char *file, int line)
{
	std::cout << "ERROR CODE: "  << ",in " << function << "  in " << file << " at " << line << std::endl;
	return true;
}
