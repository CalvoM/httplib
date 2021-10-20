//
// Created by d1r3ct0r on 10/14/21.
//

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
    this->body += body;
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
       if(line.at(k_pos+1) == ' '){
           value = line.substr(k_pos+2,string::npos);
       }else{
           value = line.substr(k_pos+1,string::npos);
       }
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