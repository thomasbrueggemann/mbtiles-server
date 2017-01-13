#include <sstream>      // std::stringbuf
#include <streambuf>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "HandleDeflate.h"
using namespace std;

void TestDec(streambuf &st)
{
	int testBuffSize = 1024*88;
	char buff[testBuffSize];
	stringstream ss;
	while(st.in_avail()>0)
	{
		//cout << st.in_avail() << endl;
		int len = st.sgetn(buff, testBuffSize-1);
		buff[len] = '\0';
		
		//cout << buff;
		ss.write(buff, len);
	}
	cout << ss.str() << endl;
}

void TestEnc(streambuf &st)
{
	char testdata2[] = "The quick brown fox jumped over the lazy brown cow.";

	st.sputn(testdata2, sizeof(testdata2));
}

int main()
{
	//This should decode to "The quick brown fox jumped over the lazy brown cow."
	const unsigned char testdata[] = {0x78, 0x9c, 0x0b, 0xc9, 0x48, 0x55, 0x28, 0x2c, \
		0xcd, 0x4c, 0xce, 0x56, 0x48, 0x2a, 0xca, 0x2f, 0xcf, 0x53, \
		0x48, 0xcb, 0xaf, 0x50, 0xc8, 0x2a, 0xcd, 0x2d, 0x48, 0x4d, \
		0x51, 0xc8, 0x2f, 0x4b, 0x2d, 0x52, 0x28, 0x01, 0xca, 0xe7, \
		0x24, 0x56, 0x55, 0x42, 0xa5, 0x93, 0xf3, 0xcb, 0xf5, 0x00, \
		0xe7, 0x94, 0x12, 0xb5};

	std::stringbuf buffer;
	buffer.sputn ((char *)testdata, sizeof(testdata));

	class DecodeDeflate decodeDeflate(buffer);
	TestDec(decodeDeflate);

	std::stringbuf buffer2;
	class EncodeDeflate *encodeDeflate = new class EncodeDeflate(buffer2);
	TestEnc(*encodeDeflate);
	delete encodeDeflate; //Note that deleting the object causes it to flush and complete the compressed output.
	//Reading the result before this is not likely to work.

	string result = buffer2.str();
	for(size_t i=0;i<result.size();i++)
		cout << std::hex << (unsigned int)(unsigned char)result[i] << ",";
	cout << endl;
}

