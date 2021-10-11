#include "Client/HTTPClient.h"

int main(int argc, char **argv){
    HTTPClient client("localhost","5000");
    client.Get("/");
}