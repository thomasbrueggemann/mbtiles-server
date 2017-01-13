#ifndef _ENCODE_GZIP_H
#define _ENCODE_GZIP_H

#include <zlib.h>
#include <streambuf>
#include <iostream>
#define ENC_MAGIC_NUM_FOR_GZIP 16

class EncodeGzip : public std::streambuf
{
protected:
	char *encodeBuff;
	std::streambuf &outStream;
	z_stream d_stream;
	std::streamsize encodeBuffSize;
	bool firstInputData;
	int compressionLevel;
	int windowBits;

	void CopyDataToOutput();

	std::streamsize xsputn (const char* s, std::streamsize n);
	int overflow (int c = EOF);

public:
	EncodeGzip(std::streambuf &outStream,
		int compressionLevel = Z_DEFAULT_COMPRESSION, 
		std::streamsize encodeBuffSize = 1024*128,
		int windowBits = MAX_WBITS+ENC_MAGIC_NUM_FOR_GZIP);
	virtual ~EncodeGzip();
};

#endif //_ENCODE_GZIP_H

