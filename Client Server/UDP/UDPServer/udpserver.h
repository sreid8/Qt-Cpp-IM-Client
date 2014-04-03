#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QUdpSocket>
#include <QDebug>
#include <string>
using std::string;
class UDPserver : public QUdpSocket
{
	Q_OBJECT

public:
	UDPserver(QObject *parent=0);
	~UDPserver();
	void openConnection();

public slots:
	void handleReadyRead();

private:
	QUdpSocket *socket;
	
};

#endif // UDPSERVER_H
