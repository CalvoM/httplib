#include "Client/HTTPClient.h"
#include "utils/base64.h"
#include <openssl/md5.h>

using std::endl;
string getUserName(){
    return "Test";
}

string getPassword(){
    return "1234";
}

int main(int argc, char **argv){
    HTTPClient client("httpbin.org");
    ParamsData p;
    string name = getUserName();
    string pass = getPassword();
    BasicAuth auth(name,pass);
    auto resp = client.Get("/digest-auth/auth/"+name+"/"+pass,nullptr,&auth);
    string body = resp.getBody();
    auto headers = resp.getHeaders();
    for(auto h:headers){
        cout<<h.first<<" : "<<h.second<<endl;
    }
    cout<<"RESPONSE STATUS: "<<resp.getResponseStatus();
}
