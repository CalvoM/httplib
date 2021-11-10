#include "DigestAuth.h"

DigestAuth::DigestAuth(DigestAuthParams *params=nullptr){
    if(params){
        this->params = *params;
        this->isParamsEmpty = false;
    }else{
        this->isParamsEmpty = true;
    }
}