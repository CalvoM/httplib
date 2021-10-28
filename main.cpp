#include "Client/HTTPClient.h"
#include "utils/base64.h"

int main(int argc, char **argv){
    HTTPClient client("neverssl.com");
    ParamsData p;
    p["marco"] = "polo";
    p["got"] = "good";
    Auth auth = make_pair("test","123£");
    auto resp = client.Get("/",&p,&auth);
    string body = resp.getBody();
    cout<<body;
}