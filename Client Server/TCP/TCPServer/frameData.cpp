#include "frameData.h"


frameData::frameData(void)
{
	data.clear();
	frame = 0;

}


frameData::~frameData(void)
{
}


void frameData::setData(QByteArray d)
{
	data=d;
}

void frameData::setFrame(int fr)
{
	frame = fr;
}

QByteArray frameData::getData()
{
	return data;
}

int frameData::getFame()
{
	return frame;
}