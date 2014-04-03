#include "udpserver.h"

UDPserver::UDPserver(QObject *parent)
	: QUdpSocket(parent)
{

}

UDPserver::~UDPserver()
{
	socket->close();
	delete socket;
}

void UDPserver::openConnection()
{
	socket = new QUdpSocket;
	if(!socket->bind(QHostAddress::Any,8065))
	{
		qDebug() << "Could not start server.";
		
	}
	else
	{
		qDebug() << "Listening on port 8065.";
		connect(socket,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
	}


}

void UDPserver::handleReadyRead()
{
	QHostAddress *userAddr;
	quint16 *userPort;
	char str[100];
	for(int i=1;i<100;i++)
		str[i]='\0';
	qint64 dataSize;
	userAddr=new QHostAddress;
	userPort = new quint16;
	dataSize = socket->pendingDatagramSize();
	socket->readDatagram(str,dataSize,userAddr,userPort);
	socket->writeDatagram(str,*userAddr,*userPort);
	delete userAddr;
	delete userPort;
}

