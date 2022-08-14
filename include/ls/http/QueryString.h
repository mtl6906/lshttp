#ifndef LS_HTTP_QUERYSTRING_H
#define LS_HTTP_QUERYSTRING_H

#include "ls/CopyableItem.h"
#include "ls/OrderedMap.h"
#include  "ls/json/Object.h"

namespace ls
{
	namespace http
	{
		class QueryString : public CopyableItem
		{
			public:
				QueryString() = default;
				QueryString(OrderedMap<std::string, std::string> &om);
				int copyTo(char *text, int len) override;
				int lengthOfString() override;
				std::string encode(const std::string &text);
				std::string decode(const std::string &text);
				std::string getParameter(int &ec, const std::string &key);
				void setParameter(const std::string &key, const std::string &value);
				OrderedMap<std::string, std::string> &getData();
			protected:
				int parse(const std::string &text) override;
				OrderedMap<std::string, std::string> om;
		};
	}
}

#endif
