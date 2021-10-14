#include "HTTPClient.h"

HTTPClient::HTTPClient(string baseUrl,string port){
    this->baseUrl = baseUrl;
    this->requestHeaders["Host"] = baseUrl;
    this->requestHeaders["User-Agent"] = "bazeengaHTTPLIB";
    this->port = port;
}

int HTTPClient::Get(string endpoint){
    string message;
    string requestLine = "GET "+endpoint+" "+this->httpVersion+this->terminator;
    this->requestHeaders["Connection"] = "keep-alive";
    this->requestHeaders["Accept"] = "*/*";
    this->requestHeaders["Accept-Encoding"] = "*";
    message += requestLine;
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
    getResponse(buffer);
    delete tcpClient;
    return 0;
}

Response* HTTPClient::getResponse(char *const buffer) {
    Response *resp;
    string bufferStr = string(buffer);
    size_t term_pos = bufferStr.find(this->terminator);
    if(term_pos == string::npos) return nullptr;
    string statusLine = bufferStr.substr(0,term_pos);
    size_t space_pos = statusLine.find(" ");
    if(space_pos == string::npos) return nullptr;
    string statusCode = statusLine.substr(space_pos+1, 3);
    resp->setResponseStatus(statusCode);
    bufferStr = bufferStr.substr(term_pos+this->terminator.size(),bufferStr.size());
    size_t headers_end_pos = bufferStr.find("\r\n\r\n");
    if(headers_end_pos == string::npos) return nullptr;
    string headers = bufferStr.substr(0,headers_end_pos);
    resp->setHeaders(headers);
    string body = bufferStr.substr(headers_end_pos+4,string::npos);
    resp->setBody(body,true);
    return resp;
}