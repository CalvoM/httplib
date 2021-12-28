#include "DigestAuth.h"
#include "../utils/utils.h"
#include <utility>

using std::make_pair;

DigestAuth::DigestAuth(DigestAuthParams *params) {
    if (params) {
        this->params = *params;
        this->isParamsEmpty = false;
    } else {
        this->isParamsEmpty = true;
    }
    this->nonSessionAlgorithms.push_back("MD5");
    this->nonSessionAlgorithms.push_back("SHA-256");
    this->nonSessionAlgorithms.push_back("SHA-512-256");
    for (string algo : this->nonSessionAlgorithms) {
        this->SessionAlgorithms.push_back(algo + "-sess");
    }
}

string DigestAuth::getHeaderValue() { return ""; }

pair<string, ErrorCode> DigestAuth::getA1Hash() {
    if (isParamsEmpty)
        return make_pair("No params provided", ErrorCode::empty_params);
    if (this->isInParams("algorithm") == false)
        return make_pair("Algorithm missing", ErrorCode::missing_params_value);
    string algorithm = this->params["algorithm"];
    if (httplib::Contains(this->nonSessionAlgorithms, algorithm) == false) {
        if (httplib::Contains(this->SessionAlgorithms, algorithm) == false)
            return make_pair("Algorithm not supported",
                             ErrorCode::invalid_algorithm);
    }
    if (this->isInParams("username") == false ||
        this->isInParams("password") == false)
        return make_pair("Username/Password missing",
                         ErrorCode::missing_params_value);
    if (this->isInParams("realm") == false)
        return make_pair("Realm missing", ErrorCode::missing_params_value);
    string digest;
    if (httplib::Contains(this->nonSessionAlgorithms, algorithm) == true) {
        string src = this->params["username"] + ":" + this->params["realm"] +
                     ":" + this->params["password"];
        if (algorithm == "MD5")
            digest = getMD5Hash(src);
        else if (algorithm == "SHA-256" or algorithm == "SHA-512-256")
            digest = getSHA256Hash(src);
    } else {
    }
    return make_pair(digest, ErrorCode::ok);
}

pair<string, ErrorCode> DigestAuth::getA2Hash() {
    string digest;
    return make_pair(digest, ErrorCode::ok);
}
string DigestAuth::getItemFromListStr(string data, string token) {
    size_t tokenPos = data.find(token);
    if (tokenPos == string::npos) {
        return data;
    } else {
        return data.substr(0, tokenPos + 1);
    }
}

bool DigestAuth::isInParams(string key) {
    if (this->params.find(key) == this->params.end())
        return false;
    return true;
}
