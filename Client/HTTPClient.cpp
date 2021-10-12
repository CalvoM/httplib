#include "HTTPClient.h"

HTTPClient::HTTPClient(string baseUrl,string port){
    this->baseUrl = baseUrl;
    this->requestHeaders["Host"] = baseUrl;
    this->requestHeaders["User-Agent"] = "bazeengaHTTPLIB";
    this->port = port;
}

int HTTPClient::Get(string endpoint){
    string message;
    string statusLine = "GET "+endpoint+" "+this->httpVersion+this->terminator;
    this->requestHeaders["Connection"] = "keep-alive";
    this->requestHeaders["Accept"] = "*/*";
    message += statusLine;
    if(!this->requestHeaders.empty()){
        for(auto h:this->requestHeaders){
            message += h.first+":"+h.second+this->terminator;
        }
    }   
    message += this->terminator;
    tcpClient = new TCPClient();
    tcpClient->Connect(this->requestHeaders["Host"],this->port);
    tcpClient->SendString(message);
    char buffer[this->maxHTTPResponseSize];
    memset(buffer,0,sizeof(buffer));
    tcpClient->Recv(buffer,sizeof(buffer));
    cout<<buffer<<strlen(buffer);
    requestHeaders.clear();
    delete tcpClient;
    return 0;
}