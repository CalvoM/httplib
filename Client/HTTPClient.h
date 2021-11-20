#ifndef HTTP_CLIENT_H_
#define HTTP_CLIENT_H_

#include "../sharedlibs/network/netutils.h"
#include "BasicAuth.h"
#include "DigestAuth.h"
#include "Response.h"
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>

using std::cout;
using std::make_pair;
using std::map;
using std::memset;
using std::pair;
using std::string;
using std::unordered_map;

using Headers = map<string, string>;
using ParamsData = unordered_map<string, string>;
using Username = string;
using Password = string;

class HTTPClient {
  public:
    HTTPClient(string baseUrl, string port = "80");
    ~HTTPClient() {}
    Response Get(string endpoint, ParamsData *params = nullptr,
                 Auth *auth = nullptr);
    void SetPort(string port) { this->port = port; }

  private:
    Auth *auth;
    string baseUrl;
    TCPClient *tcpClient;
    string port;
    Headers requestHeaders;
    Headers responseHeaders;
    const uint64_t maxHTTPResponseSize = 102400;
    const string httpMajorVersion = "1";
    const string httpMinorVersion = "1";
    const string httpVersion =
        "HTTP/" + httpMajorVersion + "." + httpMinorVersion;
    const string terminator = "\r\n";
    Response getResponse(char *const);
};

#endif
