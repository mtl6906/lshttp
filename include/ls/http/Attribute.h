#ifndef LS_HTTP_ATTRIBUTE_H
#define LS_HTTP_ATTRIBUTE_H

#include "ls/CopyableItem.h"
#include "ls/OrderedMap.h"

namespace ls
{
	namespace http
	{
		class Attribute : public CopyableItem
		{
			public:
				Attribute();
				void replace(const std::string &key, const std::string &value);
				void push(const std::string &key, const std::string &value);
				std::string get(const std::string &key);
				void clear();
				int copyTo(char *text, int len) override;
				int lengthOfString() override;
			protected:
				void parse(const std::string &text) override;
				OrderedMap<std::string, std::string> attribute;
		};
	}
}

#endif
