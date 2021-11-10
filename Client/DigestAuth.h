#ifndef DIGESTAUTH_H
#define DIGESTAUTH_H

#include "Auth.h"
#include <map>

using std::string;
using DigestAuthParams = std::map<string, string>;

class DigestAuth : public Auth{
    public:
        DigestAuth(DigestAuthParams *params=nullptr);
        ~DigestAuth();
        string getHeaderValue();
    private:
        DigestAuthParams params;
        bool isParamsEmpty;
};

#endif