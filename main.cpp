#include "Client/HTTPClient.h"


int main(int argc, char **argv){
    HTTPClient client("neverssl.com");
    auto resp = client.Get("/");
}