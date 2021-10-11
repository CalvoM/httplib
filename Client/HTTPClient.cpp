#include "HTTPClient.h"

HTTPClient::HTTPClient(string baseUrl,string port){
    this->baseUrl = baseUrl;
    this->requestHeaders["Host"] = baseUrl;
    this->port = port;
}

int HTTPClient::Get(string endpoint){
    string message;
    string statusLine = "GET "+endpoint+" "+this->httpVersion+"\r\n";
    message += statusLine;
    if(!this->requestHeaders.empty()){
        for(auto h:this->requestHeaders){
            message += h.first+":"+h.second+"\r\n";
        }
    }   
    message += "\r\n";
    tcpClient = new TCPClient();
    tcpClient->Connect(this->requestHeaders["Host"],this->port);
    tcpClient->SendString(message);
    tcpClient->Recv();
    delete tcpClient;
    return 0;
}