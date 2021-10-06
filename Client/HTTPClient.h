#ifndef HTTP_CLIENT_H_
#define HTTP_CLIENT_H_

#include <string>
#include "../sharedlibs/network/netutils.h"

using std::string;

class HTTPClient{
public:
    HTTPClient(string baseUrl);
    ~HTTPClient();
    int Get(string endpoint);
private:
    string baseUrl;
    TCPClient *tcpClient;

};

#endif