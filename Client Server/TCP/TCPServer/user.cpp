#include <QTcpSocket>
#include <QString>
#include "user.h"

User::User()
{
    socketDescriptor = 0;
    name.clear();
}

QString User::getName()
{
    return name;
}

void User::setName(QString nm)
{
    name = nm;
}

int User::getDescriptor()
{
    return socketDescriptor;
}

void User::setDescriptor(int id)
{
    socketDescriptor = id;
}

void User::clear()
{
	name.clear();
	socketDescriptor = 0;
}
