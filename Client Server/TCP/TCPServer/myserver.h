#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include <qlinkedlist.h>
#include <qmutex.h>
#include <qtimer.h>
#include "mythread.h"
#include "threadFrame.h"
#include "frameData.h"
class myserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit myserver(QObject *parent = 0);
	~myserver();
    void StartServer();
	

signals:
    
public slots:
   void cleanUp(); 
protected:
    void incomingConnection(int socketDescriptor);

private:
	QTimer *timer;
    QMutex *lock;

};

#endif // MYSERVER_H
