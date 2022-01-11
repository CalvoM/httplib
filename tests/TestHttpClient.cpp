#include "../Client/HTTPClient.h"
#include "catch.hpp"

TEST_CASE("HTTPClient", "Testing adding extra http request headers") {
    HTTPClient client("random.com");
    Headers headers;
    string usefulHeader = "X-ADDED";
    string uselessHeader = "X-NOT-ADDED";
    headers[usefulHeader] = "Random-Header-Value";
    client.AddHeaders(headers);
    Headers clientHeaders = client.GetHeaders();
    REQUIRE(clientHeaders.find(usefulHeader) != clientHeaders.end());
    REQUIRE(clientHeaders.find(uselessHeader) == clientHeaders.end());
    client.RemoveHeader(usefulHeader);
    clientHeaders = client.GetHeaders();
    REQUIRE(clientHeaders.find(usefulHeader) == clientHeaders.end());
}
