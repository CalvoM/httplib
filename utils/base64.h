#ifndef _BASE64_H_
#define _BASE64_H_

// Source: https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c
#include <string>
#include <vector>

using std::string;
using std::vector;
using BYTE = unsigned char;

string base64_encode (BYTE const *buf, unsigned int bufLen);
vector<BYTE> base64_decode (string const &);
#endif