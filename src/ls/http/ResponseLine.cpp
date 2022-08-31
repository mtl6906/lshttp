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
		ResponseLine::ResponseLine(const string &code, const string &version) : 
												code(code), 
												message(codeMapper[code]), 
												version(version)
		{
			
		}
		
		int ResponseLine::parse(const string &text)
		{
			istringstream iss(text);
			iss >> version >> code >> message;
			string tmp;
			while(iss >> tmp)
				message = message + " " + tmp;
			return Exception::LS_OK;
		}

		int ResponseLine::copyTo(char *text, int len)
		{
			int los = lengthOfString();
			if(len < los)
				return Exception::LS_EFULL;
			text = cstring::api.append(text, version.c_str());
			text = cstring::api.append(text, " ");
			text = cstring::api.append(text, code.c_str());
			text = cstring::api.append(text, " ");
			text = cstring::api.append(text, message.c_str());
			text = cstring::api.append(text, "\r\n");
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
