#ifndef LS_HTTP_STRINGBODY_H
#define LS_HTTP_STRINGBODY_H

#include "ls/http/Body.h"

namespace ls
{
	namespace http
	{
		class StringBody : public Body
		{
			public:
				StringBody(const std::string &body, const std::string &type);
				void getData(void *data) override;
				int getLength() override;
			protected:
				std::string data;
		};
	}
}

#endif
