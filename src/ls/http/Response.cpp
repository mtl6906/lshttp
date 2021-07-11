#include "ls/http/Response.h"
#include "ls/http/Code.h"
#include "ls/cstring/API.h"
#include "ls/time/API.h"
#include "ls/Exception.h"
#include "ls/io/Factory.h"
#include "sstream"
#include "memory"
#include "sys/stat.h"
#include "fcntl.h"
#include "unistd.h"

using namespace std;

namespace ls
{
	namespace http
	{
		map<string, string> suffixmapper = {
			{".html", "text/html"},
			{".css", "text/css"},
			{".js", "application/x-javascript"},
			{".pdf", "application/pdf"}
		};

		string &Response::getCode()
		{
			return rs.code;
		}

		string &Response::getMessage()
		{
			return rs.message;
		}

		string &Response::getVersion()
		{
			return rs.version;
		}

		string &Response::getBody()
		{
			return body;
		}

		void Response::setAttribute(const string &key, const string &value)
		{
			try
			{
				header.push(key, value);
			}
			catch(Exception &e)
			{
				header.replace(key, value);
			}
		}

		string Response::getAttribute(const string &key)
		{
			return header.get(key);
		}

		void Response::setDefaultHeader(Request &req)
		{
			getVersion() = req.getVersion();
			header.clear();
			header.push("Content-Encoding", "identity");
			header.push("Server", "LSS/1.0");
			header.push("Date", time::api.getServerTime());
			header.push("Connection", "close");
			int split = req.getURL().find_last_of(".");
			if(split != string::npos)
			{
				auto suffix = req.getURL().substr(split);
				header.push("Content-Type", suffixmapper[suffix]);
			}
		}

		void Response::parse(const string &text)
		{
			Buffer *buffer = new Buffer(text.size());
			buffer -> push(text);
			unique_ptr<io::InputStream> in(io::factory.makeInputStream(nullptr, buffer));
			rs.parseFrom(in -> split("\r\n", true));
			header.parseFrom(in -> split("\r\n\r\n", true));
		}

		int Response::copyTo(char *text, int len)
		{
			int los = rs.copyTo(text, len);
			los += header.copyTo(text + los, len - los);
			return los;
		}

		int Response::lengthOfString()
		{
			return rs.lengthOfString() + header.lengthOfString();
		}

		void Response::clear()
		{
			body = "";
			rs.clear();
			header.clear();
		}
	}
}
