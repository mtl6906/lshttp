#include "ls/http/Response.h"
#include "ls/http/Code.h"
#include "ls/http/Type.h"
#include "ls/cstring/API.h"
#include "ls/time/API.h"
#include "ls/file/API.h"
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
		string Response::defaultHeader = "Content-Encoding: identity\r\nServer: LSS/1.0\r\n";

		Response::Response(Buffer *buffer) : buffer(buffer)
		{
		}

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

		file::File *Response::getFile()
		{
			return file;
		}

		void Response::reset(Buffer *buffer)
		{
			this -> buffer = buffer;
		}
		
		void Response::setResponseLine(const string &code, const string &version)
		{
			buffer -> push(version);
			buffer -> push(" ");
			buffer -> push(code);
			buffer -> push(" ");
			buffer -> push(codeMapper[code]);
			buffer -> push("\r\n");
			buffer -> push(defaultHeader);
		}

		void Response::setAttribute(const string &key, const string &value)
		{
			buffer -> push(key);
			buffer -> push(": ");
			buffer -> push(value);
			buffer -> push("\r\n");
		}

		void Response::setStringBody(const string& text, const string &type)
		{

			setAttribute("Content-Length", to_string(text.size()));
			setAttribute("Content-Type", type);
			setAttribute("Date", time::api.getServerTime());
		//	setAttribute("Date", time::api.getServerTime());
			buffer -> push("\r\n");
			buffer -> push(text);
/*
			buffer -> push("Content-Type");
			buffer -> push(": ");
			buffer -> push(type);
			buffer -> push("\r\n");
			
	                buffer -> push("Content-Length");
			buffer -> push(":");
			buffer -> push(to_string(text.size()));
			buffer -> push("\r\n");
			buffer -> push("\r\n");
			buffer -> push(text);
*/			
		}

		void Response::setFileBody(const string &pathname)
		{
			if(file::api.exist(pathname))
				file = file::api.get(pathname);
			setAttribute("Content-Length", to_string(file -> size()));
			setAttribute("Content-Type", getTypeByFilename(pathname));
			setAttribute("Date", time::api.getServerTime());
			buffer -> push("\r\n");
		}

		string Response::getAttribute(const string &key)
		{
			int ec;
			return header.get(ec, key);
		}

		void Response::setHeaderByRequest(Request &request)
		{
			setAttribute("Connection", request.getConnection());
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
			buffer = nullptr;
			file = nullptr;
			rs.clear();
			header.clear();
			body = "";
		}
	}
}
