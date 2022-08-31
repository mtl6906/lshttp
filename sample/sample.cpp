#include "ls/http/Request.h"
#include "ls/http/Response.h"
#include "ls/http/QueryString.h"
#include "ls/http/Code.h"
#include "ls/http/Url.h"
#include "ls/Buffer.h"
#include "ls/io/InputStream.h"
#include "memory"

using namespace ls;
using namespace std;

int main(int argc, char **argv)
{
//	encode request
	LOGGER(ls::INFO) << "encode request:" << ls::endl;
	http::Request request;
	request.getMethod() = "GET";
	request.getURL() = "/helloworld";
	request.getVersion() = "HTTP/1.1";

	request.setDefaultHeader();
	request.setBody("helloworld, request", "text/plain");

	string text = request.toString();
	LOGGER(ls::INFO) << "requestline and header: \n" << text << ls::endl;
	LOGGER(ls::INFO) << "body:\n" << request.getBody() << ls::endl;
//	decode request
	LOGGER(ls::INFO) << "decode request:" << ls::endl;
	auto buffer = new Buffer();
	buffer -> push(text);
	buffer -> push(request.getBody());
	io::InputStream in(nullptr, buffer);
	request.clear();
	int ec;
	text = in.split(ec, "\r\n\r\n", true);
	request.parseFrom(text);
	LOGGER(ls::INFO) << "requestline and header: \n" << text << ls::endl;
	int len = stoi(request.getAttribute("Content-Length"));
	request.getBody() = in.split(ec, len);
	LOGGER(ls::INFO) << "body: \n" << request.getBody() << ls::endl;
// encode response
	LOGGER(ls::INFO) << "encode response:" << ls::endl;
	buffer -> clear();
	http::Response response(buffer);
	response.setResponseLine("200", request.getVersion());
	response.setHeaderByRequest(request);
	response.setStringBody("hello world, response", "text/plain");

	text = in.split();
	LOGGER(ls::INFO) << "response: \n" << text << ls::endl;
// decode response
	LOGGER(ls::INFO) << "decode response:" << ls::endl;
	buffer -> clear();
	buffer -> push(text);
	response.clear();
	text = in.split(ec, "\r\n\r\n", true);
	response.parseFrom(text);
	LOGGER(ls::INFO) << "responseline and header:\n" << response.toString() << ls::endl;
	len = stoi(response.getAttribute("Content-Length"));
	response.getBody() = in.split();
	LOGGER(ls::INFO) << "body:\n" << response.getBody() << ls::endl;
// decode queryString
	http::QueryString qs;
	qs.setParameter("AccessKeyId", "e2xxxxxx-99xxxxxx-84xxxxxx-7xxxx");
	qs.setParameter("SignatureMethod", "HmacSHA256");
	qs.setParameter("SignatureVersion", "2");
	qs.setParameter("Timestamp", "2017-05-11T15:19:30");
	qs.setParameter("order-id", "1234567890");
	cout << qs.encode(qs.toString()) << endl;
//	reset url
	http::Url url("/a/b/c?a=123");
	url.part[0] = "d";
	url.reset(url.part, url.queryText);
	LOGGER(ls::INFO) << url.url << ls::endl;
	
	return 0;
}
