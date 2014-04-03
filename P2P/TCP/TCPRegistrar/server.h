#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QLinkedList>
#include <QMutex>
#include <QDebug>
#include "socketthread.h"
#include "User.h"
class Server : public QTcpServer
{
	Q_OBJECT

public:
	Server(QObject *parent=0);
	~Server();
	void StartServer();

signals:

public slots:

protected:
	void incomingConnection(int socketDescriptor);


private:
	QLinkedList<User> *users;
	User *newestUser;
	QMutex *lock;
	
};

#endif // SERVER_H
