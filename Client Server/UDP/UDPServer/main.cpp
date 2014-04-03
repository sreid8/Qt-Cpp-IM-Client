
#include <QtCore/QCoreApplication>
#include "udpserver.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	UDPserver server;
	server.openConnection();

	return a.exec();
}
