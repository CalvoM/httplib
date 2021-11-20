#include "DigestAuth.h"

DigestAuth::DigestAuth(DigestAuthParams *params) {
    if (params) {
        this->params = *params;
        this->isParamsEmpty = false;
    } else {
        this->isParamsEmpty = true;
    }
}

string DigestAuth::getHeaderValue() { return ""; }

string DigestAuth::getA1Hash() {}

string DigestAuth::getA2Hash() {}
string DigestAuth::getItemFromListStr(string data, string token) {
    size_t tokenPos = data.find(token);
    if (tokenPos == string::npos) {
        return data;
    } else {
        return data.substr(0, tokenPos + 1);
    }
}
