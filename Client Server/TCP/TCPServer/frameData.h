#pragma once
#include <qbytearray.h>
class frameData
{
public:
	frameData(void);
	~frameData(void);
	void setFrame(int fr);
	void setData(QByteArray d);
	int getFame();
	QByteArray getData();
	
private:
	QByteArray data;
	int frame;
};

