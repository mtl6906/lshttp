#ifndef LS_HTTP_CODE_H
#define LS_HTTP_CODE_H

#include "string"
#include "map"

namespace ls
{
    namespace http
    {
            extern std::string _200;
            extern std::string _400;
            extern std::string _404;
            extern std::string _413;
            extern std::string _500;
            extern std::string _501;
            extern std::map<std::string, std::string> codeMapper;
    }
}

#endif