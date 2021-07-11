#include "ls/http/Attribute.h"
#include "ls/Exception.h"
#include "ls/cstring/API.h"
#include "sstream"

using namespace std;

static ls::cstring::API cstringAPI;

namespace ls
{
	namespace http
	{
		Attribute::Attribute()
		{

		}

		void Attribute::parse(const string &text)
		{
			istringstream iss(text);
			string key, value;
			while(getline(iss, key, ' ') && getline(iss, value, '\n'))
			{
				key.pop_back();
				value.pop_back();
				attribute.push(key, value);
			}
		}

		int Attribute::copyTo(char *text, int len)
		{
			int los = lengthOfString();
			if(len < los)
				throw Exception(Exception::LS_EFULL);
			for(auto &it : attribute.getData())
			{
				text = cstringAPI.append(text, it -> first.c_str());
				text = cstringAPI.append(text, ": ");
				text = cstringAPI.append(text, it -> second.c_str());
				text = cstringAPI.append(text, "\r\n");
			}
			text = cstringAPI.append(text, "\r\n");
			return los;
		}

		int Attribute::lengthOfString()
		{
			int len = 2;
			for(auto &it : attribute.getData())
				len += it -> first.size() + it -> second.size() + 4;
			return len;
		}

		void Attribute::push(const string &key, const string &value)
		{
			attribute.push(key, value);
		}

		void Attribute::replace(const string &key, const string &value)
		{
			attribute.replace(key, value);
		}

		string Attribute::get(const string &key)
		{
			return attribute.get(key);
		}

		void Attribute::clear()
		{
			attribute.clear();
		}
	}
}
