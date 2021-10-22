#include "ls/http/StringBody.h"

using namespace std;

namespace ls
{
	namespace http
	{
		StringBody::StringBody(const string &data, const string &type) : data(data), Body(type, "string")
		{
			
		}

		int StringBody::getLength()
		{
			return data.size();
		}
		
		void StringBody::getData(void *data)
		{
			*(string *)data = this -> data;
		}
	}
}
