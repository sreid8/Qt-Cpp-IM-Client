#ifndef DATA_H
#define DATA_H
#include <QByteArray>
#include <QString>
#include "user.h"
class Data
{
public:
    Data();
    QByteArray getData();
    QString getName();
    int getDescriptor();
    void setData(QByteArray stuff);
    void setName(QString user);
    void setDescriptor(int id);
	void setSendDescriptor(int id);
	int getSendDescriptor();
private:
    QByteArray data;
    User screenName;
	int sendDescriptor;
};

#endif // DATA_H
