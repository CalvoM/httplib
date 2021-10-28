#include "Client/HTTPClient.h"
#include "utils/base64.h"

int main(int argc, char **argv){
    HTTPClient client("neverssl.com");
    ParamsData p;
    p["marco"] = "polo";
    p["got"] = "good";
    auto resp = client.Get("/",&p);
    string body = resp.getBody();
    cout<<body;
    string test = "test:123£";
    string encoded = base64_encode(test);
    cout<<encoded;
}