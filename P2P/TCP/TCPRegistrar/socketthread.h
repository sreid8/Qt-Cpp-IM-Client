#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <QMutex>
#include <QLinkedList>
#include <QDebug>
#include "User.h"
#include <QTcpSocket>
#include <QTimer>

class socketThread : public QThread
{
	Q_OBJECT

public:
	socketThread(QMutex *lk, QLinkedList<User> *us, User *u, int ID, QObject *parent=0);
	~socketThread();
	void run();

signals:
	void error(QTcpSocket::SocketError sockError);
	void writeSig();
	void timeSig();

public slots:
	void handleReadyRead();
	void handleDisconnected();
	
private:
	QTcpSocket *socket;
	int socketDescriptor;
	QLinkedList<User> *users;
	User *newestUser;
	QMutex *lock;
	int numberPeers;
	
};

#endif // SOCKETTHREAD_H
