#include "reghandle.h"

RegHandle::RegHandle(QString regIP, QMutex *lk, QString *m, int *sF, QLinkedList<Data> *d, QObject *parent)
	: QThread(parent)
{
	ip = regIP;
	lock = lk;
	msgs = m;
	sysFrame = sF;
	data = d;
}

RegHandle::~RegHandle()
{

}

void RegHandle::run()
{
	//this is where this thread begins.
	socket = new QTcpSocket;
	socket->connectToHost(ip, 8060);
	if(!socket->waitForConnected())
	{
		exit(1);
	}
	connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
	//okay, ready to make new friends.
	exec();
}

void RegHandle::handleReadyRead()
{
	//this is where the stuff from the registrar
    //gets handled and clients are connected to that way
    QString otherIP;
    otherIP = socket->readAll();
    manualThread *thread = new manualThread(otherIP,lock,msgs,sysFrame,data);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();
}