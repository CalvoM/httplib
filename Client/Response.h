//
// Created by d1r3ct0r on 10/14/21.
//

#ifndef HTTPLIB_RESPONSE_H
#define HTTPLIB_RESPONSE_H
#include <string>
#include <map>
#include <iostream>
#include "../sharedlibs/network/netutils.h"
#include <zlib.h>

using std::string;
using std::map;
using std::cout;

//TODO: check the mimetypes used and see how to support them
//TODO: application,audio,example,font,image,model,video
enum class ContentTypes{
    none=-1,
    unsupported,
    text
};

enum class ContentEncoding{
    none=-1,
    unsupported,
    gzip,
    compress,
    deflate,
    br
};

using HeaderValue = string;
using HeaderKey = string;
using MIMEType = string;
using content_encoding_t = enum ContentEncoding;
using content_type_t = enum ContentTypes;
using Headers = map<HeaderKey,HeaderValue>;
using ContentTypeExtra = map<string,string>;

struct ContentTypeHeader{
    content_type_t type;
    ContentTypeExtra description;
};


class Response{
public:
    Response();
    void setHeaders(string);
    void setResponseStatus(string);
    void setBody(string,bool);
    ContentTypeHeader getContentType();
    content_encoding_t getContentEncoding();
    string getBody() const{
        return this->body;
    }
    string getResponseStatus() const{
        return this->responseStatus;
    }
    Headers getHeaders() const{
        return this->resHeaders;
    }
    string decompressGZIP(string);
private:
    Headers resHeaders;
    string responseStatus;
    string body;
};
#endif //HTTPLIB_RESPONSE_H
