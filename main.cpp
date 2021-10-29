#include "Client/HTTPClient.h"
#include "utils/base64.h"

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
    auto resp = client.Get("/basic-auth/"+name+"/"+pass,nullptr,&auth);
    string body = resp.getBody();
    auto headers = resp.getHeaders();
    cout<<body<<std::endl;
}
