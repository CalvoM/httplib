#ifndef DIGESTAUTH_H
#define DIGESTAUTH_H

#include "Auth.h"
#include <map>

using std::string;
using DigestAuthParams = std::map<string, string>;

class DigestAuth : public Auth {
  public:
    DigestAuth(DigestAuthParams *params = nullptr);
    string getHeaderValue();
    string getA1Hash();
    string getA2Hash();
    ~DigestAuth() {}

  private:
    DigestAuthParams params;
    bool isParamsEmpty;
    string getItemFromListStr(string, string);
};

#endif
