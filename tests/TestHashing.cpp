#include "../utils/hashing.h"
#include "catch.hpp"
#include <map>

using HashDigest = std::map<string, string>;

TEST_CASE("MD5", "Testing MD5 operations for the lib") {
    // using md5 hashes from https://hashtoolkit.com/common-passwords/
    HashDigest d;
    d["123456"] = "e10adc3949ba59abbe56e057f20f883e";
    d["qwerty"] = "d8578edf8458ce06fbc5bb76a58c5ca4";
    d["12345"] = "827ccb0eea8a706c4c34a16891f84e7b";
    d["dragon"] = "8621ffdbc5698829397d97767ac13db3";
    d["shadow"] = "3bf1114a986ba87ed28fc1b5884fc2f8";
    d["matrix"] = "21b72c0b7adc5c7b4a50ffcb90d92dd6";
    d["Mufasa:testrealm@host.com:Circle Of Life"] =
        "939e7578ed9e3c518a452acee763bce9";
    for (auto d_ : d) {
        REQUIRE(getMD5Hash(d_.first) == d_.second);
    }
}

TEST_CASE("SHA256", "Testing SHA256 operations for the lib") {
    // using sha256 hashes from https://hashtoolkit.com/common-passwords/
    HashDigest d;
    d["123456"] =
        "8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92";
    d["qwerty"] =
        "65e84be33532fb784c48129675f9eff3a682b27168c0ea744b2cf58ee02337c5";
    d["12345"] =
        "5994471abb01112afcc18159f6cc74b4f511b99806da59b3caf5a9c173cacfc5";
    d["dragon"] =
        "a9c43be948c5cabd56ef2bacffb77cdaa5eec49dd5eb0cc4129cf3eda5f0e74c";
    d["shadow"] =
        "0bb09d80600eec3eb9d7793a6f859bedde2a2d83899b70bd78e961ed674b32f4";
    d["matrix"] =
        "6e00cd562cc2d88e238dfb81d9439de7ec843ee9d0c9879d549cb1436786f975";
    for (auto d_ : d) {
        REQUIRE(getSHA256Hash(d_.first) == d_.second);
    }
}
