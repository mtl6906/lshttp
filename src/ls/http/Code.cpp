#include "ls/http/Code.h"

using namespace std;

namespace ls
{
    namespace http
    {
        string _200("200");
        string _400("400");
        string _404("404");
        string _413("413");
        string _500("500");
        string _501("501");
        map<string, string> codeMapper({
            {_200, "OK"},
            {_400, "Bad Request"},
            {_404, "Not Found"},
            {_413, "Request Entity Too Large"},
            {_500, "Internal Server Error"},
            {_501, "Not Implemented"}
        });
    }
}