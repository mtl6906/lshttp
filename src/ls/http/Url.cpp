#include "ls/http/Url.h"
#include "ls/Buffer.h"
#include "ls/DefaultLogger.h"
#include "ls/algorithm.h"
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
			if(split == std::string::npos || url == "/")
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
//			LOGGER(ls::INFO) << "part: [";
//			for(int i=0;i<part.size();++i)
//					logger << " " << part[i] << " ";
//			logger << "]" << ls::endl;
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

		void Url::reset(vector<string> &part, const string &qs)
		{
			if(part.size() == 0)
				*this = Url("/");
			int length = ls::size(part) + part.size();
			if(qs.size() > 0)
				length += qs.size() + 1;
			Buffer buffer(length);
			for(auto &p : part)
			{
				buffer.push("/", 1);
				buffer.push(p);
			}
			if(qs != "")
			{
				buffer.push("?", 1);
				buffer.push(qs);
			}
			*this = Url(buffer.getData());
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
