#include "data.h"

Data::Data()
{
    data.clear();
    screenName.setName("");
    screenName.setDescriptor(0);
}

QString Data::getName()
{
    return screenName.getName();
}

int Data::getDescriptor()
{
    return screenName.getDescriptor();
}

QByteArray Data::getData()
{
    return data;
}

void Data::setData(QByteArray stuff)
{
    data=stuff;
}

void Data::setDescriptor(int id)
{
    screenName.setDescriptor(id);
}

void Data::setName(QString user)
{
    screenName.setName(user);
}

void Data::setSendDescriptor(int id)
{
	sendDescriptor = id;
}

int Data::getSendDescriptor()
{
	return sendDescriptor;
}