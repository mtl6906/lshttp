#include "ls/http/QueryString.h"
#include "ls/cstring/API.h"
#include "ls/Buffer.h"
#include "sstream"

using namespace std;

namespace ls
{
	namespace http
	{
		QueryString::QueryString(OrderedMap<std::string, std::string> &om) : om(om)
		{
		
		}

		int QueryString::parse(const string &text)
		{
			istringstream iss(text);
			string key, value;
			while(getline(iss, key, '=') && getline(iss, value, '&'))
				om.push(key, value);
			return Exception::LS_OK;
		}

		int QueryString::copyTo(char *text, int len)
		{
			int los = lengthOfString();
			if(len < los)
				return Exception::LS_EFULL;
			auto v = om.getData();
			for(int i=0;i<v.size()-1;++i)
			{
				auto it = v[i];
				text = cstring::api.append(text, it -> first.c_str());
				text = cstring::api.append(text, "=");
				text = cstring::api.append(text, it -> second.c_str());
				text = cstring::api.append(text, "&");
			}
			text = cstring::api.append(text, v.back() -> first.c_str());
			text = cstring::api.append(text, "=");
			text = cstring::api.append(text, v.back() -> second.c_str());
			return los;
		}

		int QueryString::lengthOfString()
		{
			auto &data = om.getData();
			int len = data.size() << 1;
			for(auto it : data)
				len += it -> first.size() + it -> second.size();
			return len - 1;
		}

		string QueryString::encode(const std::string &text)
		{
			char spch[4];
			Buffer buffer(3*text.size());
			string validset = "=&$-_.+!*'(),";
			for(auto &ch : text)
			{
				if((ch <= '9' && ch >= '0') ||
					(ch <= 'z' && ch >= 'a') ||
					(ch<= 'Z' && ch >= 'A') ||
					(validset.find_first_of(ch) != string::npos))
					{
						buffer.push(&ch, 1);
						continue;
					}
				snprintf(spch, sizeof(spch), "%%%02X", ch);
				buffer.push(spch, 3);
			}
			string result(buffer.size(), '\0');
			buffer.pop(result);
			return result;
		}

		string QueryString::decode(const std::string &text)
		{
			char ch;
			Buffer buffer(text.size());
			for(int i=0;i<text.size();++i)
			{
				if(text[i] == '%')
				{
					sscanf((char *)text.c_str()+i+1, "%X", &ch);
					i+=3;
					buffer.push(&ch, 1);
				}
				else
					buffer.push(&ch, 1);
			}
			string result(buffer.size(), '\0');
			buffer.pop(result);
			return result;
		}

		string QueryString::getParameter(const string &key)
		{
			int ec;
			return om.get(ec, key);
		}

		void QueryString::setParameter(const string &key, const string &value)
		{
			if(om.push(key, value) < 0)
				om.replace(key, value);
		}

		OrderedMap<string, string> &QueryString::getData()
		{
			return om;
		}
	}
}
