#include "Client/HTTPClient.h"


int main(int argc, char **argv){
    HTTPClient client("eu.httpbin.org");
    auto resp = client.Get("/");
    cout<<resp.getBody();
}