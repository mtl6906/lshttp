#ifndef LS_HTTP_COOKIE_H
#define LS_HTTP_COOKIE_H

#include "ls/CopyableItem.h"
#include "ls/OrderedMap.h"

namespace ls
{
    namespace http
    {
        class Cookie : public CopyableItem
        {
            public:
                Cookie() = default;
                void setExpire(int timeout);
                void setPath(const std::string &path);
                void setDomain(const std::string &domain);
                void setSecure(bool secure);
                void setHttpOnly(bool httpOnly);
                void setCookie(const std::string &key, const std::string &value);
                std::string getCookie(int &ec, const std::string &key);
                int copyTo(char *text, int len) override;
                int lengthOfString() override;
            protected:
                int parse(const std::string &text)override;
                OrderedMap<std::string, std::string> om;
                std::string expire;
                std::string path;
                std::string domain;
                bool secure = false;
                bool httpOnly = false;
        };
    }
}

#endif
