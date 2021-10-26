#include "Response.h"
#include <math.h>
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
    switch(encoding){
        case ContentEncoding::none:
            this->body = body;
            break;
        case ContentEncoding::gzip:
        case ContentEncoding::br:
        case ContentEncoding::compress:
        case ContentEncoding::deflate:
            cout<<"Response Content-Encoding Not supported!"<<endl;
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

//* compressed data manipulation 
//! Needs more work
//TODO improve decompression process
string Response::decompressGZIP(string body, int size){
    unsigned char* data = new unsigned char[size];
    unsigned int i=0;
    while(size>0){
        data[i] = body.c_str()[i];
        size--;
        i++;
    }
    z_stream strm = {0};
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = data;
    strm.avail_in = size;
    int z_status = inflateInit2(&strm,MAX_WBITS|32);
    cout<<z_status;
    int ret = -1;
    switch( z_status )
    {
        case Z_OK:
        case Z_STREAM_END:
        case Z_BUF_ERROR:
            z_status = inflate(&strm,Z_FINISH);
            if (z_status == Z_STREAM_END){
                ret = strm.total_out;
                cout<<ret;
            }
            else{
            cout<<"END"<<endl;
            inflateEnd(&strm);
            return "";
            }
            break;
        default:
            inflateEnd( &strm );
            fprintf( stderr, "Gzip error %d.\n", z_status);
            return "";
    }

    return "";
}

unsigned int Response::hexToInt(string hex){
    int power = hex.size() -1;
    unsigned int finalNum=0;
    for(auto c: hex){
        finalNum += (c-'0')*int(pow(16,power));
        power--;
    }
    return finalNum;
}