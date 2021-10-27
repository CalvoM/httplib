#include "Client/HTTPClient.h"

int main(int argc, char **argv){
    HTTPClient client("neverssl.com");
    ParamsData p;
    p["marco"] = "polo";
    p["got"] = "good";
    auto resp = client.Get("/",&p);
    string body = resp.getBody();
    cout<<body;
}