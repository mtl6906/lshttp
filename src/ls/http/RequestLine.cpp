#include "ls/http/RequestLine.h"
#include "ls/cstring/API.h"
#include "ls/DefaultLogger.h"
#include "ls/Exception.h"
#include "sstream"
#include "iostream"
#include "algorithm"

#define REQUESTLINE_LOG "REQUESTLINE_LOG"

using namespace std;

static ls::cstring::API api;

static vector<string> validMethod({
	"GET", "POST", "DELETE", "PUT"
});

namespace ls
{
	namespace http
	{
		void RequestLine::parse(const string &text)
		{
			istringstream iss(text);
			iss >> method;
			if(find(validMethod.begin(), validMethod.end(), method) == validMethod.end())
				throw Exception(Exception::LS_EFORMAT);
			iss >> url;
			if(url.find("/../") != string::npos || url.substr(url.size() - 3, 3) == "/..")
				throw Exception(Exception::LS_EFORMAT);
			iss >> version;
			if(version != "HTTP/1.1")
				throw Exception(Exception::LS_EFORMAT);
			LOGGER(ls::INFO) << "method: " << method << ls::endl;
			LOGGER(ls::INFO) << "url: " << url << ls::endl;
			LOGGER(ls::INFO) << "version: " << version << ls::endl;
		}

		int RequestLine::lengthOfString()
		{
			return method.size() + url.size() + version.size() + 4;
		}

		int RequestLine::copyTo(char *text, int len)
		{
			int los = lengthOfString();
			if(len < los)
				throw Exception(Exception::LS_EFULL);
			text = api.append(text, method.c_str());
			text = api.append(text, " ");
			text = api.append(text, url.c_str());
			text = api.append(text, " ");
			text = api.append(text, version.c_str());
			text = api.append(text, "\r\n");
			return los;
		}

		void RequestLine::clear()
		{
			method = "";
			url = "";
			version = "";
		}
	}
}
