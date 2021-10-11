#ifndef HTTP_CLIENT_H_
#define HTTP_CLIENT_H_

#include <string>
#include <map>
#include "../sharedlibs/network/netutils.h"

using std::string;
using std::map;

class HTTPClient{
public:
    HTTPClient(string baseUrl, string port="80");
    ~HTTPClient(){}
    int Get(string endpoint);
    void SetPort(string port){
        this->port = port;
    }
private:
    string baseUrl;
    TCPClient *tcpClient;
    string port;
    map<string,string> requestHeaders;
    const string httpMajorVersion="1";
    const string httpMinorVersion="1";
    const string httpVersion = "HTTP/"+httpMajorVersion+"."+httpMinorVersion;
};

#endif