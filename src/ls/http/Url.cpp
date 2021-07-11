#include "ls/http/Url.h"
#include "ls/DefaultLogger.h"
#include "sstream"

#define URL_LOG "URL_LOG"

using namespace std;

namespace ls
{
	namespace http
	{
		Url::Url(const string &url) : url(url)
		{
			int split = url.find_first_of("/");
			if(split == std::string::npos)
			{
				uri = "/";
				queryText = "";
				part.clear();
			}
			else
			{
				int n = splitQueryText();
				splitURI(n);
				splitPart();
			}
			LOGGER(ls::INFO) << "url: " << url << ls::endl;
			LOGGER(ls::INFO) << "uri: " << uri << ls::endl;
			LOGGER(ls::INFO) << "part: [";
			for(int i=0;i<part.size()-1;++i)
					logger << part[i] << ",";
 			logger << *part.rbegin() << "]" << ls::endl;
		}

		int Url::splitQueryText()
		{
			int n = url.find_first_of("?");
			if(string::npos != n)
				queryText = url.substr(n + 1);
			else
				queryText = "";
			return n;
		}

		void Url::splitURI(int n)
		{
			uri = url.substr(0, n);
		}

		void Url::splitPart()
		{
			istringstream iss(uri.substr(1));
			string text;
			while(getline(iss, text, '/'))
				part.push_back(std::move(text));
		}

		void Url::clear()
		{
			url = "";
			uri = "";
			queryText = "";
			part.clear();
		}
	}
}
