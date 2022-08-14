#include "ls/http/Type.h"
#include "ls/http/FileBody.h"
#include "ls/file/API.h"
#include "ls/Exception.h"

using namespace std;

namespace ls
{
	namespace http
	{
		FileBody::FileBody(const string &filename) : file(nullptr), Body(getTypeByFilename(filename), "file")
		{
			if(file::api.exist(filename))
				file = file::api.get(filename);
		}

		FileBody::~FileBody()
		{
			if(file != nullptr)
				delete file;
		}

		int FileBody::getLength()
		{
			return file -> size();
		}

		void FileBody::getData(void *data)
		{
			*(file::File **)data = file;
		}
	}
}
