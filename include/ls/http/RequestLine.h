#ifndef LS_HTTP_REQUESTLINE_H
#define LS_HTTP_REQUESTLINE_H

#include "ls/CopyableItem.h"

namespace ls
{
	namespace http
	{
		class RequestLine : public CopyableItem
		{
			public:
				RequestLine() = default;
				void clear();
				int copyTo(char *text, int len) override;
				int lengthOfString() override;

				std::string method;
				std::string url;
				std::string version;
			protected:
				void parse(const std::string &text);
		};

	}
}

#endif
