#ifndef HASHING_H_
#define HASHING_H_
#include "cryptopp/cryptlib.h"
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/md5.h"
#include "cryptopp/sha.h"
#include <algorithm>
#include <string>

using std::string;

// gives the MD5 digest of the string message provided.
static string getMD5Hash(string message) {
    string digest;
    CryptoPP::Weak::MD5 hash;
    hash.Update((const CryptoPP::byte *)&message[0], message.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte *)&digest[0]);
    string final_digest;
    CryptoPP::StringSource ss(
        digest, true,
        new CryptoPP::HexEncoder(new CryptoPP::StringSink(final_digest)));
    std::transform(final_digest.begin(), final_digest.end(),
                   final_digest.begin(), ::tolower);
    return final_digest;
}

// gives the SHA256 digest of the string message provided.
static string getSHA256Hash(string message) {
    string digest;
    CryptoPP::SHA256 hash;
    hash.Update((const CryptoPP::byte *)&message[0], message.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte *)&digest[0]);
    string final_digest;
    CryptoPP::StringSource ss(
        digest, true,
        new CryptoPP::HexEncoder(new CryptoPP::StringSink(final_digest)));
    std::transform(final_digest.begin(), final_digest.end(),
                   final_digest.begin(), ::tolower);
    return final_digest;
}

#endif
