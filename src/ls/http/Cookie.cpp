#include "ls/http/Cookie.h"
#include "ls/time/API.h"
#include "ls/cstring/API.h"
#include "ls/Exception.h"
#include "sstream"

using namespace std;
using namespace ls;

namespace ls
{
	namespace http
	{
		void Cookie::setExpire(int timeout)
		{
			expire = time::api.getCookieTime(timeout);
		}

		void Cookie::setPath(const string &path)
		{
			this -> path = path;
		}

		void Cookie::setDomain(const string &domain)
		{
			this -> domain = domain;
		}

		void Cookie::setSecure(bool secure)
		{
			this -> secure = secure;
		}

		void Cookie::setCookie(const string &key, const string &value)
		{
			try
			{
				om.push(key, value);
			}
			catch(Exception &e)
			{
				om.replace(key, value);
			}
		}

		void Cookie::setHttpOnly(bool httpOnly)
		{
			this -> httpOnly = httpOnly;
		}

		int Cookie::copyTo(char *text, int len)
		{
			int los = lengthOfString();
			if(len < los)
				throw Exception(Exception::LS_EFULL);
			for(auto &it : om.getData())
			{
				text = cstring::api.append(text, it -> first.c_str());
				text = cstring::api.append(text, "=");
				text = cstring::api.append(text, it -> second.c_str());
				text = cstring::api.append(text, ",");
			}
			*(text - 1) = ';';
			text = cstring::api.append(text, " ");
			if(expire != "")
			{
				text = cstring::api.append(text, "Expires=");
				text = cstring::api.append(text, expire.c_str());
				text = cstring::api.append(text, "; ");
			}
			if(domain != "")
			{
				text = cstring::api.append(text, "Domain=");
				text = cstring::api.append(text, domain.c_str());
				text = cstring::api.append(text, "; ");
			}
			if(path != "")
			{
				text = cstring::api.append(text, "Path=");
				text = cstring::api.append(text, path.c_str());
				text = cstring::api.append(text, "; ");
			}
			if(secure)
				text = cstring::api.append(text, "SECURE; ");
			if(httpOnly)
				text = cstring::api.append(text, "HttpOnly; ");
			return los;
		}

		int Cookie::lengthOfString()
		{
		//	',' and '='
			int len = 2 * om.getData().size() + 1;
			for(auto &it : om.getData())
				len += it -> first.size() + it -> second.size();
		//	"Expires=" + "; "
			if(expire != "")
				len += 8 + expire.size() + 2;
		//	"Domain=" + "; "
			if(domain != "")
				len += 7 + domain.size() + 2;
		//	"Path=" + "; "
			if(path != "")
				len += 5 + path.size() + 2;
		//	"SECURE; "
			if(secure)
				len += 8;
		//	"HttpOnly; "
			if(httpOnly)
				len += 10;
			return len;
		}

		void Cookie::parse(const string &data)
		{
			istringstream sin(data);
			string key, value, p;
			while(getline(sin, p, ' '))
			{
				istringstream sinp(p);
				if(getline(sin, key, '=') && getline(sinp, value, ';'))
					setCookie(key, value);
			}
		}

		string Cookie::getCookie(const string &key)
		{
			return om.get(key);
		}
	}
}
