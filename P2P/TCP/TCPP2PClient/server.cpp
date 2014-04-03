#include "server.h"
#include "manualthread.h"
#include "newconnthread.h"

Server::Server(QMutex *lk, QString *mg, QLinkedList<Data> *d, int *sF,QString a, int p, QObject *parent) :
    QTcpServer(parent)
{
    regAddress = a;
    regPort = p;
    sysFrame = sF;
    data = d;
    msgs = mg;
    lock = lk;
}

void Server::StartServer()
{
    /* this server is unique in that it is not only a server
     *for incomming connections, but that it is a client of
     *the registrar. This makes it a complex class to write.*/

    //first, lets do the Client portions of it.
  /*  socket = new QTcpSocket;
    socket->connectToHost(regAddress,regPort);
    if(!socket->waitForConnected())
    {
        //the socket will wait for 30 seconds and try to connect
        //if it doesn't connect, it does this.
        exit(1);
    }
    connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    //the server will get all the ip address of all the clients as they come in from the
    //handleReadyRead slot.*/

	//THIS IS WHERE THE REGISTRAR WILL BE CONNECTED TO!
	//I decided to use separate the jobs of the server into threads... hopefully that fixes some of the issues.
	RegHandle *handler;
	handler = new RegHandle(regAddress,lock,msgs,sysFrame,data);
	connect(handler,SIGNAL(finished()),handler,SLOT(deleteLater()));
	handler->start();

    //Now to make this class a server....

    if(!this->listen(QHostAddress::Any,8061))
    {
        //if it can't listen, then the server couldn't
        //be started, so exit.
        exit(1);
    }
    //otherwise, I'm open for business.
}

void Server::incomingConnection(int socketDescriptor)
{
    //this is where the clients that connect to this
    //server get handled.
    newConnThread *thread = new newConnThread(lock,msgs,sysFrame,socketDescriptor,data);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();
}

/*void Server::handleReadyRead()
{
    //this is where the stuff from the registrar
    //gets handled and clients are connected to that way
    QString otherIP;
    otherIP = socket->readAll();
    manualThread *thread = new manualThread(otherIP,lock,msgs,sysFrame,data);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();
}*/
