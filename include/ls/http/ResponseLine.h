#ifndef LS_HTTP_RESPONSELINE_H
#define LS_HTTP_RESPONSELINE_H

#include "ls/CopyableItem.h"

namespace ls
{
	namespace http
	{
		class ResponseLine : public CopyableItem
		{
			public:
				ResponseLine() = default;
				void clear();
				int copyTo(char *text, int len) override;
				int lengthOfString() override;
				std::string version;
				std::string code;
				std::string message;
			protected:
				int parse(const std::string &text) override;
		};
	}
}

#endif
