#include "ls/http/QueryString.h"
#include "ls/cstring/API.h"
#include "sstream"

using namespace std;
using ls::cstring::api;

namespace ls
{
	namespace http
	{
		void QueryString::parse(const string &text)
		{
			istringstream iss(text);
			string key, value;
			while(getline(iss, key, '=') && getline(iss, value, '&'))
				om.push(key, value);
		}

		int QueryString::copyTo(char *text, int len)
		{
			int los = lengthOfString();
			if(len < los)
				throw Exception(Exception::LS_EFULL);
			for(auto it : om.getData())
			{
				text = api.append(text, it -> first.c_str());
				text = api.append(text, "=");
				text = api.append(text, it -> second.c_str());
				text = api.append(text, "&");
			}
			*(text - 1) = '\0';
			return los;
		}

		int QueryString::lengthOfString()
		{
			auto &data = om.getData();
			int len = data.size() << 1;
			for(auto it : data)
				len += it -> first.size() + it -> second.size();
			return len - 1;
		}
	}
}
