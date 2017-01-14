#ifndef _DECODE_GZIP_H
#define _DECODE_GZIP_H

#include <zlib.h>
#include <streambuf>
#define DEC_MAGIC_NUM_FOR_GZIP 16

class DecodeGzip : public std::streambuf
{
protected:
	char *readBuff;
	char *decodeBuff;
	std::streambuf &inStream;
	z_stream d_stream;
	bool decodeDone;
	char *decodeBuffCursor;
	std::streamsize readBuffSize, decodeBuffSize;

	void Decode();

	//Override streambuf virtual methods
	std::streamsize xsgetn (char* s, std::streamsize n);
	int uflow();
	std::streamsize showmanyc();

public:
	DecodeGzip(std::streambuf &inStream, 
		std::streamsize readBuffSize = 1024*128, std::streamsize decodeBuffSize = 1024*128,
				int windowBits = MAX_WBITS+DEC_MAGIC_NUM_FOR_GZIP);
	virtual ~DecodeGzip();
};

#endif //_DECODE_GZIP_H

