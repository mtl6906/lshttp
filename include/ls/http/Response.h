#ifndef LS_HTTP_RESPONSE_H
#define LS_HTTP_RESPONSE_H

#include "ls/http/Request.h"
#include "ls/http/ResponseLine.h"
#include "ls/http/Attribute.h"
#include "ls/CopyableItem.h"
#include "ls/http/Body.h"
#include "map"
#include "memory"

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
				Body *getBody();
				void setCode(const std::string &code);
				void setBody(Body *body);
				void setDefaultHeader(Request &req);
				void setAttribute(const std::string &key, const std::string &value);
				std::string getAttribute(int &ec, const std::string &key);
				void clear();
				int copyTo(char *text, int len) override;
				int lengthOfString() override;
			protected:
				int parse(const std::string &text) override;
				ResponseLine rs;
				Attribute header;
				std::unique_ptr<Body> body;
		};
	}
}
#endif
