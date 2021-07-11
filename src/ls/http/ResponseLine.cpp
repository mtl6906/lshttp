#include "ls/http/ResponseLine.h"
#include "ls/http/Code.h"
#include "ls/Exception.h"
#include "ls/cstring/API.h"
#include "sstream"

using namespace std;

namespace ls
{
	namespace http
	{
		void ResponseLine::parse(const string &text)
		{
			istringstream iss(text);
			iss >> version >> code >> message;
		}

		int ResponseLine::copyTo(char *text, int len)
		{
			int los = lengthOfString();
			if(len < los)
				throw Exception(Exception::LS_EFULL);
			text = ls::cstring::api.append(text, version.c_str());
			text = ls::cstring::api.append(text, " ");
			text = ls::cstring::api.append(text, code.c_str());
			text = ls::cstring::api.append(text, " ");
			text = ls::cstring::api.append(text, message.c_str());
			text = ls::cstring::api.append(text, "\r\n");
			return los;
		}

		int ResponseLine::lengthOfString()
		{
			return code.size() + version.size() + message.size() + 4;
		}

		void ResponseLine::clear()
		{
			code = "";
			version = "";
			message = "";
		}
	}
}
