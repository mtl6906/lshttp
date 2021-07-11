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
				int copyTo(char *text, int len) override;
				int lengthOfString() override;
			protected:
				void parse(const std::string &text) override;
				OrderedMap<std::string, std::string> om;
		};
	}
}

#endif
