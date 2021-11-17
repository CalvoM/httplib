#include "DigestAuth.h"

DigestAuth::DigestAuth(DigestAuthParams *params){
    if(params){
        this->params = *params;
        this->isParamsEmpty = false;
    }else{
        this->isParamsEmpty = true;
    }
}

string DigestAuth::getHeaderValue(){
    return "";
}
