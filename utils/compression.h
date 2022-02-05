#ifndef COMPRESSION_H_
#define COMPRESSION_H_
#include <string>
#include <zconf.h>
#include <zlib.h>
#include <assert.h>
#include <iostream>
#include <cstring>

#define SET_BINARY_MODE(file)
using std::string;
using std::cout;
using std::endl;

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
        string InflateData(string, unsigned int);
    private:
        string gzipInflate(string);
        string deflateInflate(string);
        string zlibInflate(string);
        int inflateData(string, string &);
        CompressionAlgorithm compressionAlgo;
        int inflateWindowBits;
        unsigned int dataSize;
};

Compression::Compression(CompressionAlgorithm algo){
    this->compressionAlgo = algo;
    this->inflateWindowBits = MAX_WBITS;
    this->dataSize = 0;
}

string Compression::InflateData(string data, unsigned int size){
    this->dataSize = size;
    switch(this->compressionAlgo){
        case CompressionAlgorithm::zlib:{
            this->inflateWindowBits = MAX_WBITS;
            return this->zlibInflate(data);
        }
        case CompressionAlgorithm::gzip: {
            this->inflateWindowBits = MAX_WBITS + 16;
            string dest;
            inflateData(data, dest);
            return this->gzipInflate(data);
        }
        case CompressionAlgorithm::deflate: {
            this->inflateWindowBits = -MAX_WBITS;
            return this->deflateInflate(data);
        }
        default:{
            return data;
        }
    }
}

string Compression::gzipInflate(string data){
    return "";
}
string Compression::zlibInflate(string data){
    return "";

}
string Compression::deflateInflate(string data){
    return "";

}
int Compression::inflateData(string src, string &dest){
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = Z_NULL;
    strm.next_in = Z_NULL;
    int status = inflateInit2(&strm, this->inflateWindowBits);
    if(status != Z_OK) return status;
    unsigned char in[this->dataSize];
    unsigned char out[this->dataSize];
    unsigned have;
    do {
        std::strcpy(in, src.c_str());
        strm.avail_in = this->dataSize;
        if(ferror(src)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if(strm.avail_in == 0)
            break;
        strm.next_in = in;
        do {
            strm.avail_out = chunk;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);
            switch(ret){
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    (void)inflateEnd(&strm);
                    return ret;
            }
            have = chunk - strm.avail_out;
            if(fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        }while (strm.avail_out == 0);
    }while (ret != Z_STREAM_END);
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
    return 0;
}
int comp_inf(FILE *src, FILE *dest) {
    int chunk = 16384;
    unsigned char in[chunk];
    unsigned char out[chunk];
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = Z_NULL;
    strm.next_in = Z_NULL;
    int ret = inflateInit2(&strm, 16+MAX_WBITS);
    if(ret != Z_OK){
        return ret;
    }
    unsigned have;
    do {
        strm.avail_in = fread(in, 1, chunk, src);
        if(ferror(src)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if(strm.avail_in == 0)
            break;
        strm.next_in = in;
        do {
            strm.avail_out = chunk;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);
            switch(ret){
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    (void)inflateEnd(&strm);
                    return ret;
            }
            have = chunk - strm.avail_out;
            if(fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        }while (strm.avail_out == 0);
    }while (ret != Z_STREAM_END);
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}
#endif
