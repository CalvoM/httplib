#include "Client/HTTPClient.h"
#include <zlib.h>

void compressBody(string body){
    const char *pData = body.c_str();
    size_t dataSize = body.size();
    cout<<"Initial body size: "<<dataSize<<std::endl;
    size_t compressedDataSize = dataSize;
    unsigned char* compressedData = new unsigned char[compressedDataSize];
    int result = compress2(compressedData,&compressedDataSize,(const unsigned char*)pData,dataSize,9);
    if(result == Z_OK){
        cout<<"Compressed size: "<<compressedDataSize<<std::endl;

    }else{
        cout<<"Issue during compression";
    }
    delete []compressedData;
}

int main(int argc, char **argv){
    HTTPClient client("eu.httpbin.org");
    auto resp = client.Get("/");
    string body = resp.getBody();
    compressBody(body);
}