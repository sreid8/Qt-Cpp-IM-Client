#ifndef NEWCONNTHREAD_H
#define NEWCONNTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QLinkedList>
#include <QMutex>
#include <QTimer>
#include "User.h"
#include "data.h"


class newConnThread : public QThread
{
    Q_OBJECT
public:
    explicit newConnThread(QMutex *lk, QString *d, int *sF, int ID, QLinkedList<Data> *s, QObject *parent = 0);
    ~newConnThread();
    void run();
    
signals:
    void timeSig();
    
public slots:
    void handleReadyRead();
    void handleDisconnected();
    void handleWrite();
    void handleTimeout();

private:
    int socketDescriptor;
    QTcpSocket *socket;
    QTimer *timer;
    QMutex *lock;
    QString *data;
    QLinkedList<Data> *sendData;
    int *sysFrame;
    int threadFrame;

};

#endif // NEWCONNTHREAD_H
