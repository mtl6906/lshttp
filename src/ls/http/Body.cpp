#include "ls/http/Body.h"

using namespace std;

namespace ls
{
	namespace http
	{
		Body::Body(const string &type, const string &tag) : type(type), tag(tag)
		{
		
		}

		Body::~Body()
		{
		
		}

		string &Body::getType()
		{
			return type;
		}

		string &Body::getTag()
		{
			return tag;
		}
	}
}
