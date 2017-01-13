//g++ ReadGzip.cpp TestGzip.cpp -lz -o readgzip
#include <fstream>
#include <iostream>
#include "DecodeGzip.h"
#include "EncodeGzip.h"

using namespace std;

void TestDec(streambuf &st)
{
	int testBuffSize = 1024*88;
	char buff[testBuffSize];
	ofstream testOut("testout.txt", ios::binary);
	while(st.in_avail()>0)
	{
		//cout << st.in_avail() << endl;
		int len = st.sgetn(buff, testBuffSize-1);
		buff[len] = '\0';
		cout << len << ", " << testBuffSize-1 << endl;
		
		//cout << buff;
		testOut.write(buff, len);
	}
	testOut.flush();
}

void TestEnc(streambuf &st)
{
	int testBuffSize = 1024*77;
	char buff[testBuffSize];
	ifstream testIn("input.txt", ios::binary);
	if (testIn.fail())
	{
		throw runtime_error("Failed to open input file.");		
	}
	unsigned outlen = 0;
	while(!testIn.eof())
	{
		//cout << st.in_avail() << endl;
		testIn.read(buff, testBuffSize);
		streamsize len = testIn.gcount();

		//cout << buff;
		st.sputn(buff, len);
		outlen += len;
		cout << len << "\t" << testBuffSize-1 << "\t" << outlen << endl;
	}
}

int main()
{
	//Perform decoding
	std::filebuf fb;
	fb.open("test.txt.gz", std::ios::in | std::ios::binary);
	
	class DecodeGzip decodeGzip(fb);
	TestDec(decodeGzip);

	//Perform encoding
	std::filebuf fb2;
	fb2.open("output.txt.gz", std::ios::out | std::ios::binary);
	
	class EncodeGzip *encodeGzip = new EncodeGzip(fb2, Z_DEFAULT_COMPRESSION);
	TestEnc(*encodeGzip);
	delete encodeGzip;
}

