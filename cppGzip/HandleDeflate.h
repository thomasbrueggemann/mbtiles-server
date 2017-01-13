#ifndef _HANDLE_DEFLATE_H
#define _HANDLE_DEFLATE_H
#include "DecodeGzip.h"
#include "EncodeGzip.h"

class DecodeDeflate : public DecodeGzip
{
public:
	DecodeDeflate(std::streambuf &inStream, std::streamsize readBuffSize = 1024*128, 
		std::streamsize decodeBuffSize = 1024*128, int windowSize = MAX_WBITS) : 
		DecodeGzip(inStream, readBuffSize, decodeBuffSize, windowSize)
	{}
	virtual ~DecodeDeflate() {}
};

class EncodeDeflate : public EncodeGzip
{
public:
	EncodeDeflate(std::streambuf &outStream, int compressionLevel = Z_DEFAULT_COMPRESSION,
		std::streamsize encodeBuffSize = 1024*128, int windowSize = MAX_WBITS) :
		EncodeGzip(outStream, compressionLevel, encodeBuffSize, windowSize)
	{}
	virtual ~EncodeDeflate() {}
};

#endif //_HANDLE_DEFLATE_H

