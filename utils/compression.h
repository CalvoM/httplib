#ifndef COMPRESSION_H_
#define COMPRESSION_H_
#include <string>
using std::string;

enum class CompressionAlgorithm{
    zlib,
    gzip,
    deflate,
    br,
    compress
};

class Compression{
    public:
        Compression(CompressionAlgorithm algo);
        string inflateData(string);
    private:
};

#endif
