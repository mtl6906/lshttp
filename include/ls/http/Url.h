#ifndef LS_HTTP_URL_H
#define LS_HTTP_URL_H

#include "vector"
#include "string"
#define LS_MAX_URL_LENGTH 2083

namespace ls
{
	namespace http
	{
		class Url
		{
			public:
				Url() = default;
				Url(const std::string& url);
				Url(Url &&o) = default;
				Url &operator=(Url &&o) = default;
				void clear();
				void reset(std::vector<std::string> &part, const std::string &qs);
				std::string url;
				std::string uri;
				std::string queryText;
				std::vector<std::string> part;
			protected:
				void splitURI(int n);
				void splitPart();
				int splitQueryText();
		};
	}
}

#endif
