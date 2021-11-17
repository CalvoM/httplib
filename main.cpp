#include "Client/HTTPClient.h"

using std::endl;
string getUserName(){
    return "Test";
}

string getPassword(){
    return "1234";
}

int main(int argc, char **argv){
    HTTPClient client("httpbin.org");
    string endpoint = "/digest-auth/auth/"+getUserName()+"/"+getPassword();
    ParamsData p;
    DigestAuthParams dp;
    dp["username"] = getUserName();
    dp["password"] = getPassword();
    dp["realm"] = "me@kennethreitz.com";
    dp["nonce"] = "edf1b8edeb7715866a369bff47879b9d";
    dp["uri"] = "/";
    dp["opaque"] = "0a5e8548048594ae37e1acc4921f5664";
    dp["qop"] = "auth";
    dp["algorithm"] = "MD5";
    dp["uri"] = endpoint;
    DigestAuth auth(&dp);
    auto resp = client.Get(endpoint,nullptr,&auth);
    string body = resp.getBody();
    auto headers = resp.getHeaders();
    for(auto h:headers){
        cout<<h.first<<" : "<<h.second<<endl;
    }
    cout<<"RESPONSE STATUS: "<<resp.getResponseStatus();
    cout<<"RESPONSE BODY: "<<body<<endl;
} 

