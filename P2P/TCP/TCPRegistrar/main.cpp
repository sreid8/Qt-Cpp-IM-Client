
#include <QtCore/QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Server server;
	server.StartServer();
	return a.exec();
}
