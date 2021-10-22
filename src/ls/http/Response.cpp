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
#include "cstring"

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

		Body *Response::getBody()
		{
			return body.get();
		}

		void Response::setBody(Body *body)
		{
			this -> body.reset(body);
			setAttribute("Content-Length", to_string(body -> getLength()));
			setAttribute("Content-Type", body -> getType());
		}

		void Response::setCode(const string &code)
		{
			rs.code = code;
			rs.message = codeMapper[code];
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
			body.reset(nullptr);
			rs.clear();
			header.clear();
		}
	}
}
