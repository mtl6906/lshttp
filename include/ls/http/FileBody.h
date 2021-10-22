#ifndef LS_HTTP_FILEBODY_H
#define LS_HTTP_FILEBODY_H

#include "ls/http/Body.h"
#include "ls/file/File.h"

namespace ls
{
	namespace http
	{
		class FileBody : public Body
		{
			public:
				FileBody(const std::string &filename);
				~FileBody() override;
				int getLength() override;
				void getData(void *data) override;
			protected:
				file::File *file;
		};
	}
}

#endif
