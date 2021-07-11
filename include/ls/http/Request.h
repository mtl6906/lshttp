#ifndef LS_HTTP_REQUEST_H
#define LS_HTTP_REQUEST_H

#include "string"
#include "map"
#include "memory"
#include "ls/http/RequestLine.h"
#include "ls/http/Attribute.h"
#include "ls/DefaultLogger.h"

extern std::map<int, std::string> codeMapper;
extern std::map<std::string, std::string> messageMapper;

namespace ls
{
	namespace http
	{
		class Request : public CopyableItem
		{
			public:
				Request() = default;
				std::string &getMethod();
				std::string &getVersion();
				std::string &getBody();
				std::string &getURL();
				void setDefaultHeader();
				std::string getAttribute(const std::string &key);
				void setAttribute(const std::string &key, const std::string &value);
				void clear();
				int copyTo(char *text, int len) override;
				int lengthOfString() override;
//				friend io::InputStream *operator>>(io::InputStream *in, Request &request);
//				friend io::OutputStream *operator<<(io::OutputStream *out, Request &request);
			protected:
				void parse(const std::string &text) override;
				RequestLine rq;
				Attribute header;
				std::string body;
		};
/*
		struct _Request
		{
			RequestLine rq;
			Attribute header;
			std::string body;
			int status;
			int filesize;
			std::unique_ptr<file::File> file;
		};

		RequestLine makeRequestLine(const std::string &requestline);
*/
	}
}

#endif
