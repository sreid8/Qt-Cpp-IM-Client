#ifndef MANUALTHREAD_H
#define MANUALTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include <QMutex>
#include <QLinkedList>
#include <QHostAddress>
#include "data.h"

class manualThread : public QThread
{
    Q_OBJECT
public:
    explicit manualThread(QString ip, QMutex *lk, QString *d, int *sF, QLinkedList<Data> *s, QObject *parent = 0);
    void run();

    
signals:
    void timeSig();

    
public slots:
    void handleReadyRead();
    void handleWrite();
    void handleTimeout();
    void handleDisconnected();

private:
    QTcpSocket *socket;
    QTimer *timer;
    QMutex *lock;
    QString *data;
    QLinkedList<Data> *sendData;
    int *sysFrame;
    int threadFrame;
    QString hostAddr;
    
};

#endif // MANUALTHREAD_H
