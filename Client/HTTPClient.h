#ifndef HTTP_CLIENT_H_
#define HTTP_CLIENT_H_

#include <string>
#include <map>
#include <unordered_map>
#include <iostream>
#include "../sharedlibs/network/netutils.h"
#include "Response.h"

using std::string;
using std::map;
using std::unordered_map;
using std::memset;
using std::cout;

using Headers = map<string,string>;
using ParamsData = unordered_map<string,string>;

class HTTPClient{
public:
    HTTPClient(string baseUrl, string port="80");
    ~HTTPClient(){}
    Response Get(string endpoint, ParamsData* params=nullptr);
    void SetPort(string port){
        this->port = port;
    }
private:
    string baseUrl;
    TCPClient *tcpClient;
    string port;
    Headers requestHeaders;
    Headers responseHeaders;
    const uint64_t maxHTTPResponseSize = 102400;
    const string httpMajorVersion="1";
    const string httpMinorVersion="1";
    const string httpVersion = "HTTP/"+httpMajorVersion+"."+httpMinorVersion;
    const string terminator="\r\n";
    Response getResponse(char* const);
};

#endif