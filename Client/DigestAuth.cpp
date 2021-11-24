#include "DigestAuth.h"
#include <utility>

using std::make_pair;

DigestAuth::DigestAuth(DigestAuthParams *params) {
    if (params) {
        this->params = *params;
        this->isParamsEmpty = false;
    } else {
        this->isParamsEmpty = true;
    }
}

string DigestAuth::getHeaderValue() { return ""; }

pair<string, ErrorCode> DigestAuth::getA1Hash() {
    if (isParamsEmpty)
        return make_pair("No params provided", ErrorCode::empty_params);
    if (this->params.find("algorithm") == this->params.end())
        return make_pair("Algorithm missing", ErrorCode::missing_params_value);
}

pair<string, ErrorCode> DigestAuth::getA2Hash() {}
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
