#include "server.h"
#include <QThread>
#include "socketthread.h"

Server::Server(QObject *parent)
	: QTcpServer(parent)
{

}

Server::~Server()
{

}

void Server::StartServer()
{
	//this is where I start the server. First, make some variables.
	users = new QLinkedList<User>;
	newestUser = new User;
	lock = new QMutex;
	//Now to start the server.
	if(!this->listen(QHostAddress::Any,8060))
	{
		exit(1);
	}
	else
	{
		qDebug() << "Listening on port 8060";
	}
	//nice, socket is open. Moving right along.
}

void Server::incomingConnection(int socketDescriptor)
{
	qDebug() << socketDescriptor << "Connecting...";
	socketThread *thread = new socketThread(lock,users,newestUser,socketDescriptor); //more stuff here.
	connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
	thread->start();
}
