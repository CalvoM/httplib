#ifndef URI_H_
#define URI_H_

#include <iostream>
#include <regex>
#include <string>

using std::regex;
using std::regex_match;
using std::smatch;
using std::string;

typedef struct {
    string scheme;
    string host;
    int port;
    string absPath;
    string query;
} uri_t;

// http_URL = "http:" "//" host [ ":" port ] [ abs_path [ "?" query ]]

// Return http uri details from the provided url string
uri_t *GetHTTPURIDetails(string url) {
    uri_t *uri;
    regex url_regex(
        R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)",
        regex::extended);
    smatch url_match_res;
    uint32_t counter = 0;
    if (regex_match(url, url_match_res, url_regex)) {
        for (const auto &res : url_match_res) {
            std::cout << counter++ << ": " << res << std::endl;
        }
        return uri;
    } else {
        return uri;
    }
    return uri;
}
#endif