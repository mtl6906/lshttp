#include "ls/http/Type.h"
#include "ls/cstring/API.h"

using namespace std;

namespace ls
{
	namespace http
	{
		map<string, string> typeMapper = {
			{"json", "application/json"},
			{"js", "application/javascript"},
			{"html", "text/html"},
			{"css", "text/css"},
			{"pdf", "application/pdf"},
			{"", "octet-stream"}
		};

		string getTypeByFilename(const string &filename)
		{
			auto suffix = cstring::api.suffix(filename);
			auto type = typeMapper.find(suffix);
			if(type == typeMapper.end())
				return "text/plain";
			return type -> second;
		}
	}
}
