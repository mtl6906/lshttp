#include "ls/http/Request.h"
#include "ls/http/Url.h"
#include "ls/http/QueryString.h"
#include "ls/Exception.h"
#include "ls/time/API.h"
#include "ls/DefaultLogger.h"
#include "ls/io/Factory.h"
#include "ls/Buffer.h"
#include "cstring"
#include "iostream"
#include "memory"

#define REQUEST_LOG "REQUEST_LOG"

using namespace std;

namespace ls
{
	namespace http
	{
		void Request::setDefaultHeader()
		{
			header.clear();
			header.push("Accept", "buffer/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
			header.push("Accept-Language", "zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2");
			header.push("Accept-Encoding", "deflate,br");
			header.push("Connection", "close");
		}

		string &Request::getMethod()
		{
			return rq.method;
		}

		string &Request::getURL()
		{
			return rq.url;
		}

		string &Request::getVersion()
		{
			return rq.version;
		}

		Body *Request::getBody()
		{
			return body.get();
		}

		void Request::setBody(Body *body)
		{
			this -> body.reset(body);
			setAttribute("Content-Length", to_string(body -> getLength()));
			setAttribute("Content-Type", body -> getType());
		}

		void Request::clear()
		{
			rq.clear();
			header.clear();
			body.reset(nullptr);
		}

		string toLower(string text)
		{
			for(int i=0;i<text.size();++i)
				if(text[i] >= 'A' && text[i] <= 'Z')
					text[i] += 32;
			return text;
		}

		string Request::getAttribute(const string &key)
		{
			try
			{
				return header.get(key);
			}
			catch(Exception &e)
			{
			}
			return header.get(toLower(key));
		}

		void Request::setAttribute(const string &key, const string &value)
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

		int Request::copyTo(char *text, int len)
		{
			int los = rq.copyTo(text, len);
			los += header.copyTo(text + los, len - los);
			return los;
		}

		int Request::lengthOfString()
		{
			return rq.lengthOfString() + header.lengthOfString();
		}

		void Request::parse(const string &text)
		{
			Buffer *buffer = new Buffer(text.size());
			buffer -> push(text);
			unique_ptr<io::InputStream> in(io::factory.makeInputStream(nullptr, buffer));
			rq.parseFrom(in -> split("\r\n", true));
			LOGGER(ls::INFO) << "requestline parse ok..." << ls::endl;
			header.parseFrom(in -> split("\r\n\r\n", true));
			LOGGER(ls::INFO) << "header parse ok..." << ls::endl;
		}

/*
 *
		io::InputStream *operator>>(io::InputStream *in, Request &request)
		{
			if(request.status == 0)
			{
				auto text = in -> split("\r\n");
				request.rq.parseFrom(text);
				++request.status;
			}
			if(request.status == 1)
			{
				auto text = in -> split("\r\n\r\n");
				request.attribute.parseFrom(text);
				++request.status;
			}
			return in;
		}

		io::OutputStream *operator<<(io::OutputStream *out, Request &request)
		{
			out -> append(request.rq.toString());
			out -> append(request.attribute.toString());
			out -> append(request.body);
			return out;
		}

		_RequestLine makeRequestLine(io::OutputStream *in)
		{
			_RequestLine requestline;
			requestline.method = in -> split(" ");
			requestline.URL =
		}
*/
	}
}
