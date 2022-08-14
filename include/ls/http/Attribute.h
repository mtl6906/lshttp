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
				int replace(const std::string &key, const std::string &value);
				int push(const std::string &key, const std::string &value);
				std::string get(int &ec, const std::string &key);
				void clear();
				int copyTo(char *text, int len) override;
				int lengthOfString() override;
			protected:
				int parse(const std::string &text) override;
				OrderedMap<std::string, std::string> attribute;
		};
	}
}

#endif
