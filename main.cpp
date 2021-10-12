#include "Client/HTTPClient.h"

int main(int argc, char **argv){
    HTTPClient client("scratchpads.org");
    client.Get("/explore/sites-list");
}