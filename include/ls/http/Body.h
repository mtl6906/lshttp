#ifndef LS_HTTP_BODY_H
#define LS_HTTP_BODY_H

#include "string"

namespace ls
{
	namespace http
	{
		class Body
		{
			public:
				Body(const std::string &type, const std::string &tag);
				virtual ~Body();
				virtual int getLength() = 0;
				virtual void getData(void *data) = 0;
				std::string& getType();
				std::string& getTag();
			protected:
				std::string type;
				std::string tag;
		};
	}
}

#endif
