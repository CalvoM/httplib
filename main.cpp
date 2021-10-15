#include "Client/HTTPClient.h"

int main(int argc, char **argv){
    HTTPClient client("scratchpads.org");
    auto resp = client.Get("/explore/sites-list");
    cout<<resp.getBody();
}