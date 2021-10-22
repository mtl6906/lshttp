#ifndef LS_HTTP_TYPE_H
#define LS_HTTP_TYPE_H

#include "map"
#include "string"

namespace ls
{
	namespace http
	{
		extern std::map<std::string, std::string> typeMapper;
		std::string getTypeByFilename(const std::string &filename);
	}
}

#endif
