#include "Huffman.h"
#include <assert.h>
#include <vector>

using std::vector;

class CInputBitStream {
public:
	CInputBitStream(IInputStream& _stream);
	bool ReadBit(bool& value);
	bool ReadByte(byte& value);
private:
	IInputStream& stream;
	byte lastByte; // Последний байт, считанный из stream
	char readBitsCount; // Количество считанных бит из lastByte
};


CInputBitStream::CInputBitStream(IInputStream& _stream): 
	stream(_stream),
	lastByte(0),
	readBitsCount(8)
{ }

bool CInputBitStream::ReadBit(bool& value) {
	assert(readBitsCount <= 8);
	if(readBitsCount == 8) {
		if(!stream.Read(lastByte))
			return false;
		readBitsCount = 0;
	}	
	readBitsCount++;
	value = (lastByte >> ((8 - readBitsCount)) & 1) != 0;
	return true;
}

bool CInputBitStream::ReadByte(byte& value) {
	assert(readBitsCount <= 8);
	assert(readBitsCount != 0);

	if(readBitsCount == 8) {
		return stream.Read(value);
	}
	const byte upper = lastByte << readBitsCount;
	if(!stream.Read(lastByte))
		return false;
	const byte lower = lastByte >> (8 - readBitsCount);
	value = upper | lower;
	return true;
}

class CInputStream : public IInputStream {
public:
	explicit CInputStream(vector<byte>&& source);
	virtual bool Read(byte& value) override;
private:
	vector<byte> data;
	int readBytesCount;
};

CInputStream::CInputStream(vector<byte>&& source) :
	data(std::move(source)),
	readBytesCount(0)
{

}

bool CInputStream::Read(byte& value) {
	if(readBytesCount >= data.size())
		return false;
	value = data[readBytesCount++];
	return true;
}

int main() {
	vector<byte> source = { 3, 8, 255, 0, 1 };
	CInputStream inputStream(std::move(source));
	CInputBitStream inputBitStream(inputStream);
	bool value = false;
	inputBitStream.ReadBit(value);
	return 0;
}