#ifndef LS_HTTP_RESPONSE_H
#define LS_HTTP_RESPONSE_H

#include "ls/http/Request.h"
#include "ls/http/ResponseLine.h"
#include "ls/http/Attribute.h"
#include "ls/CopyableItem.h"
#include "ls/file/File.h"
#include "ls/time/API.h"
#include "ls/http/Body.h"
#include "ls/Buffer.h"
#include "map"
#include "memory"

namespace ls
{
	namespace http
	{
		class Response : public CopyableItem
		{
			public:
				Response(Buffer *buffer = nullptr);
				std::string &getCode();
				std::string &getMessage();
				std::string &getVersion();
				std::string &getBody();
				file::File *getFile();
				void setResponseLine(const std::string &code, const std::string &version);
				void setHeaderByRequest(Request &request);
				void setAttribute(const std::string &key, const std::string &value);
				std::string getAttribute(const std::string &key);
				void setStringBody(const std::string &text, const std::string &type);
				void setFileBody(const std::string &pathname);
				void clear();
				int copyTo(char *text, int len) override;
				int lengthOfString() override;
				void reset(Buffer *buffer);
			protected:
				int parse(const std::string &text) override;
				ResponseLine rs;
				Attribute header;
				std::string body;
				Buffer *buffer;
				file::File *file;
				static std::string defaultHeader;
		};
	}
}
#endif
