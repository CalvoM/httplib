#include "Response.h"
using std::exception;
using std::stoi;
using std::endl;

Response::Response() {
    this->body.clear();
    this->responseStatus.clear();
}

void Response::setBody(string body, bool newRequest) {
    if(body.size() == 0) return;
    if(newRequest) this->body.clear();
    content_encoding_t encoding = this->getContentEncoding();
    ContentTypeHeader contentType = this->getContentType();
    size_t nlPos;
    switch(encoding){
        case ContentEncoding::none:
            this->body = body;
            break;
        case ContentEncoding::gzip:
            nlPos = body.find("\r\n");
            if(nlPos == string::npos){
                cout<<"GZIP parsing error"<<endl;
                break;
            }
            body = body.substr(nlPos+2);
            decompressGZIP(body);
            break;
        case ContentEncoding::unsupported:
        default:
            cout<<"Content-Encoding is unsupported as yet";
    }
}
void Response::setHeaders(string headers) {
   size_t l_pos,k_pos;
   string line;
   string key;
   string value;
   string terminator = "\r\n";
   while((l_pos = headers.find(terminator)) != string::npos){
       line = headers.substr(0,l_pos);
       k_pos = line.find(":");
       if(k_pos == string::npos) return;
       key = line.substr(0,k_pos);
       if(line.at(k_pos+1) == ' ') value = line.substr(k_pos+2,string::npos);
       else value = line.substr(k_pos+1,string::npos);
       this->resHeaders[key] = value;
       headers = headers.substr(l_pos+terminator.size(),string::npos);
   }
}
void Response::setResponseStatus(string code) {
    if(code.size() == 0 or code.size() != 3){
        cout<<"Invalid status code"<<std::endl;
        return;
    }
    try{
        stoi(code);
    }catch(const exception& e){
        cout<<e.what();
        return;
    }
    this->responseStatus = code;
    return;
}

content_encoding_t Response::getContentEncoding(){
    content_encoding_t resEncoding = ContentEncoding::none;
    auto encodingHeader = this->resHeaders.find("Content-Encoding");
    if(encodingHeader == this->resHeaders.end()) return resEncoding; //*No content-encoding header
    auto commaPos = encodingHeader->second.find(",");
    HeaderValue encoding;
    if(commaPos == string::npos) encoding = encodingHeader->second;
    else encoding = encodingHeader->second.substr(0,commaPos); //*incase of multiple encoding choose the first option

    if(encoding == "gzip") resEncoding = ContentEncoding::gzip;
    else if(encoding == "compress") resEncoding = ContentEncoding::compress;
    else if(encoding == "deflate") resEncoding = ContentEncoding::deflate;
    else if(encoding == "br") resEncoding = ContentEncoding::br;
    else resEncoding = ContentEncoding::unsupported;
    return resEncoding;
}

ContentTypeHeader Response::getContentType(){
    ContentTypeHeader resContentType;
    resContentType.type = ContentTypes::none;
    auto contentTypeHeader = this->resHeaders.find("Content-Type");
    if(contentTypeHeader == this->resHeaders.end()) return resContentType; //* No content-type header
    auto slashPos = contentTypeHeader->second.find("/");
    if(slashPos == string::npos) return resContentType; //* an issue with the header
    HeaderValue type;
    type = contentTypeHeader->second.substr(0,slashPos);
    if(type == "text"){
        resContentType.type = ContentTypes::text;
    }else{
        resContentType.type = ContentTypes::unsupported;
    }
    auto commaPos = contentTypeHeader->second.find(";");
    if(commaPos = string::npos) return resContentType;
    HeaderValue extra = contentTypeHeader->second.substr(commaPos+1);
    auto equalPos = extra.find("=");
    if(equalPos == string::npos) return resContentType;
    HeaderValue key = extra.substr(0,equalPos);
    resContentType.description[key] = extra.substr(equalPos+1);
    return resContentType;
}

string Response::decompressGZIP(string body){
    z_stream strm = {0};
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = Z_NULL;
    strm.avail_in = 0;
    return "";
}