#include "catch.hpp"
#include "../utils/hashing.h"
#include <map>

using HashDigest = std::map<string,string>;

TEST_CASE("MD5","Testing MD5 operations for the lib"){
// using md5 hashes from https://hashtoolkit.com/common-passwords/
    HashDigest d;
    d["123456"] = "e10adc3949ba59abbe56e057f20f883e";
    d["qwerty"] = "d8578edf8458ce06fbc5bb76a58c5ca4";
    d["12345"] = "827ccb0eea8a706c4c34a16891f84e7b";
    d["dragon"] = "8621ffdbc5698829397d97767ac13db3";
    d["shadow"] = "3bf1114a986ba87ed28fc1b5884fc2f8";
    d["matrix"] = "21b72c0b7adc5c7b4a50ffcb90d92dd6";
    for(auto d_:d){
        REQUIRE(getMD5Hash(d_.first) == d_.second); 
    }
}
