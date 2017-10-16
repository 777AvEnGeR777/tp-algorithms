#pragma once
#define interface struct

typedef unsigned char byte;

interface IInputStream {
	virtual ~IInputStream() {}
	virtual bool Read(byte& value) = 0;
};

interface IOutputStream {
	virtual ~IOutputStream() {}
	virtual bool Write(byte& value) = 0;
};