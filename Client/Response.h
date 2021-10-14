//
// Created by d1r3ct0r on 10/14/21.
//

#ifndef HTTPLIB_RESPONSE_H
#define HTTPLIB_RESPONSE_H
#include <string>
#include <map>
#include <iostream>
#include "../sharedlibs/network/netutils.h"

using std::string;
using std::map;
using std::cout;

using Headers = map<string,string>;

class Response{
public:
    Response();
    void setHeaders(string);
    void setResponseStatus(string);
    void setBody(string,bool);
private:
    Headers resHeaders;
    string responseStatus;
    string body;
};
#endif //HTTPLIB_RESPONSE_H
