#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QLinkedList>
#include <QMutex>
#include <QTcpSocket>
#include "User.h"
#include "data.h"
#include "reghandle.h"


class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QMutex *lk, QString *mg, QLinkedList<Data> *d, int *sF, QString a, int p, QObject *parent = 0);
    void StartServer();
    
signals:
    
public slots:
   // void handleReadyRead();

protected:
    void incomingConnection(int socketDescriptor);

private:
    QString regAddress;
    int regPort;
    QTcpSocket *socket;
    QMutex *lock;
    QString *msgs;
    QLinkedList<Data> *data;
    int *sysFrame;
    
};

#endif // SERVER_H
