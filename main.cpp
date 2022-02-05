#include "Client/HTTPClient.h"

using std::endl;
string getUserName() { return "Test"; }

string getPassword() { return "1234"; }

int main(int argc, char **argv) {
    HTTPClient client("httpbin.org");
    //string endpoint =
    //    "/digest-auth/auth/" + getUserName() + "/" + getPassword();
    string endpoint = "/gzip";
    ParamsData p;
    DigestAuthParams dp;
    dp["username"] = getUserName();
    dp["password"] = getPassword();
    dp["realm"] = "me@kennethreitz.com";
    dp["nonce"] = "42116d2e40dd34c9db62b11506acc3d9";
    dp["opaque"] = "2e2e829f23f25f4a5795fa16dcbe2d0c";
    dp["qop"] = "auth,auth-int";
    dp["algorithm"] = "MD5";
    dp["uri"] = endpoint;
    dp["method"] = "GET";
    DigestAuth auth(&dp);
    Response resp;
    ErrorCode err;
    Headers header;
    header["X-RANDOM"] = "WoW";
    client.AddHeaders(header);
    client.RemoveHeader("X-RANDOM");
    std::tie(resp, err) = client.Get(endpoint, nullptr, &auth);
    if (err != ErrorCode::ok) {
        return -1;
    }
    string body = resp.getBody();
    auto headers = resp.getHeaders();
    for (auto h : headers) {
        cout << h.first << " : " << h.second << endl;
    }
    cout << "RESPONSE STATUS: " << resp.getResponseStatus() << endl;
    cout << "RESPONSE BODY: " << body << endl;
}
