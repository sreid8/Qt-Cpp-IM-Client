#ifndef USER_H
#define USER_H
#include <QTcpSocket>
#include <QString>
#include <QTcpSocket>

class User
{
public:
    User();
    QString getName();
    void setName(QString nm);
    int getDescriptor();
    void setDescriptor(int id);
	void clear();


private:
QString name;
int socketDescriptor;

};




#endif // USER_H
