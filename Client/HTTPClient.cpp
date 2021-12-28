#include "HTTPClient.h"
#include <memory>

using std::unique_ptr;

HTTPClient::HTTPClient(string baseUrl, string port) {
    this->baseUrl = baseUrl;
    this->requestHeaders["Host"] = baseUrl;
    this->requestHeaders["User-Agent"] = "bazeengaHTTPLIB";
    this->port = port;
    this->tcpClient = nullptr;
}

// Sends GET request to the endpoint
Response HTTPClient::Get(string endpoint, ParamsData *params, Auth *auth) {
    if (params != nullptr) { // params to be added to the url
        endpoint += "?";
        for (auto p : *params) {
            endpoint += p.first;
            endpoint += "=";
            endpoint += p.second;
            endpoint += "&";
        }
        endpoint = endpoint.substr(0, endpoint.size() - 1);
    }
    if (auth != nullptr) {
        this->requestHeaders["Authorization"] = auth->getHeaderValue();
    }
    string message;
    string requestLine =
        "GET " + endpoint + " " + this->httpVersion + this->terminator;
    this->requestHeaders["Connection"] = "close";
    this->requestHeaders["Accept"] = "*/*";
    this->requestHeaders["Accept-Encoding"] = "identity";
    message += requestLine;
    if (!this->requestHeaders.empty()) {
        for (auto h : this->requestHeaders) {
            message += h.first + ":" + h.second + this->terminator;
        }
    }
    message += this->terminator;
    unique_ptr<TCPClient> tcpClient(new TCPClient());
    tcpClient->Connect(this->requestHeaders["Host"], this->port);
    tcpClient->SendString(message);
    char buffer[this->maxHTTPResponseSize];
    memset(buffer, 0, sizeof(buffer));
    tcpClient->Recv(
        buffer, sizeof(buffer)); //*could use the number of bytes returned later
    Response resp = getResponse(buffer);
    tcpClient->Disconnect();
    return resp;
}

Response HTTPClient::getResponse(char *const buffer) {
    unique_ptr<Response> resp(new Response);
    string bufferStr = string(buffer);
    size_t term_pos = bufferStr.find(this->terminator);
    if (term_pos == string::npos)
        return *resp;
    string statusLine = bufferStr.substr(0, term_pos);
    size_t space_pos = statusLine.find(" ");
    if (space_pos == string::npos)
        return *resp;
    string statusCode = statusLine.substr(space_pos + 1, 3);
    resp->setResponseStatus(statusCode);
    bufferStr =
        bufferStr.substr(term_pos + this->terminator.size(), bufferStr.size());
    size_t headers_end_pos = bufferStr.find("\r\n\r\n");
    if (headers_end_pos == string::npos)
        return *resp;
    string headers = bufferStr.substr(0, headers_end_pos);
    resp->setHeaders(headers);
    string body = bufferStr.substr(headers_end_pos + 4, string::npos);
    resp->setBody(body, true);
    return *resp;
}