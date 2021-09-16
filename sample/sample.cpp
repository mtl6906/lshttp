#include "ls/http/Request.h"
#include "ls/http/Response.h"
#include "ls/http/QueryString.h"
#include "ls/http/Code.h"
#include "ls/Adapter.h"
#include "ls/io/Factory.h"
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

	request.getBody() = "helloworld, request";

	request.setDefaultHeader();
	request.setAttribute("Content-Length", to_string(request.getBody().size()));

	string text = request.toString();

	LOGGER(ls::INFO) << "requestline and header: \n" << text << ls::endl;
	LOGGER(ls::INFO) << "body:\n" << request.getBody() << ls::endl;
//	decode request
	LOGGER(ls::INFO) << "decode request:" << ls::endl;
	auto buffer = new Buffer();
	buffer -> push(text);
	buffer -> push(request.getBody());
	unique_ptr<io::InputStream> in(io::factory.makeInputStream(nullptr, buffer));
	request.clear();
	text = in -> split("\r\n\r\n", true);
	request.parseFrom(text);
	LOGGER(ls::INFO) << "requestline and header: \n" << text << ls::endl;

	int len = stoi(request.getAttribute("Content-Length"));
	request.getBody() = in -> split(len);
	LOGGER(ls::INFO) << "body: \n" << request.getBody() << ls::endl;
// encode response
	LOGGER(ls::INFO) << "encode response:" << ls::endl;
	http::Response response;
	response.getCode() = http::_200;
	response.getMessage() = http::codeMapper[http::_200];
	response.setDefaultHeader(request);
	response.getBody() = "hello world, response";
	response.setAttribute("Content-Length", to_string(response.getBody().size()));

	text = response.toString();
	LOGGER(ls::INFO) << "responseline and header: \n" << text << ls::endl;
	LOGGER(ls::INFO) << "body:\n" << response.getBody() << ls::endl;
// decode response
	LOGGER(ls::INFO) << "decode response:" << ls::endl;
	buffer -> clear();
	buffer -> push(text);
	buffer -> push(response.getBody());
	response.clear();
	text = in -> split("\r\n\r\n", true);
	response.parseFrom(text);
	LOGGER(ls::INFO) << "responseline and header:\n" << response.toString() << ls::endl;
	len = stoi(response.getAttribute("Content-Length"));
	response.getBody() = in -> split(len);
	LOGGER(ls::INFO) << "body:\n" << response.getBody() << ls::endl;
// decode queryString
	http::QueryString qs;
	cout << qs.encode("AccessKeyId=e2xxxxxx-99xxxxxx-84xxxxxx-7xxxx&SignatureMethod=HmacSHA256&SignatureVersion=2&Timestamp=2017-05-11T15:19:30&order-id=1234567890") << endl;
	return 0;
}
