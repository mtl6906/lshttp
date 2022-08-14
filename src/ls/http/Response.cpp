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
			if(header.push(key, value) < 0)
				header.replace(key, value);
		}

		string Response::getAttribute(int &ec, const string &key)
		{
			return header.get(ec, key);
		}

		void Response::setDefaultHeader(Request &req)
		{
			getVersion() = req.getVersion();
			header.clear();
			header.push("Content-Encoding", "identity");
			header.push("Server", "LSS/1.0");
			header.push("Date", time::api.getServerTime());
			int ec;
			auto keepalive = req.getAttribute(ec, "Connection");
			if(ec < 0)
				header.push("Connection", "close");
			else
				header.push("Connection", keepalive);
		}

		int Response::parse(const string &text)
		{
			int ec = Exception::LS_OK;
			unique_ptr<Buffer> buffer(new Buffer(text.size()));
			buffer -> push(text);
			unique_ptr<io::InputStream> in(io::factory.makeInputStream(nullptr, buffer.get()));
			auto rstext = in -> split(ec, "\r\n", true);
			if(ec < 0)
				return ec;
			ec = rs.parseFrom(rstext);
			if(ec < 0)
				return ec;
			auto headertext =in -> split(ec, "\r\n\r\n", true);
			if(ec < 0)
				return ec;
			return header.parseFrom(headertext);
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
