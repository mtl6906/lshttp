#ifndef LS_HTTP_RESPONSE_H
#define LS_HTTP_RESPONSE_H

#include "map"
#include "ls/http/Request.h"
#include "ls/http/ResponseLine.h"
#include "ls/http/Attribute.h"
#include "ls/CopyableItem.h"

namespace ls
{
	namespace http
	{
		class Response : public CopyableItem
		{
			public:
				Response() = default;
				std::string &getCode();
				std::string &getMessage();
				std::string &getVersion();
				std::string &getBody();
				void setDefaultHeader(Request &req);
				void setAttribute(const std::string &key, const std::string &value);
				std::string getAttribute(const std::string &key);
				void clear();
				int copyTo(char *text, int len) override;
				int lengthOfString() override;
			protected:
				void parse(const std::string &text) override;
				ResponseLine rs;
				Attribute header;
				std::string body;
		};
	}
}
#endif
